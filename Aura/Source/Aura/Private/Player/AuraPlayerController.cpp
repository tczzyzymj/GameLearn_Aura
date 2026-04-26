// Copyright NineForce Entertainment

#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGASEnumManager.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayAbilityBlueprint.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates     = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	if (bAutoRunning)
	{
		if (APawn* TargetPawn = GetPawn())
		{
			FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(
				TargetPawn->GetActorLocation(),
				ESplineCoordinateSpace::World
			);
			FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(
				LocationOnSpline,
				ESplineCoordinateSpace::World
			);
			TargetPawn->AddMovementInput(Direction);

			const float DistanceToDes = (LocationOnSpline - CachedDestination).Length();
			if (DistanceToDes <= AutoRunAcceptanceRadius)
			{
				bAutoRunning = false;
			}
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn())
		);
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetControlRotation(FRotator::ZeroRotator);

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()
	);
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor   = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeGameAndUI);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraEnhancedInputComponent* EnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

	check(InputConfigDataAsset);
	EnhancedInputComponent->BindAbilityActions(
		InputConfigDataAsset,
		this,
		&ThisClass::AbilityInputPressed,
		&ThisClass::AbilityInputReleased,
		&ThisClass::AbilityInputHeld
	);
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		return;
	}

	LastHoverActor = CurHoverActor;
	CurHoverActor  = HitResult.GetActor();

	if (LastHoverActor != nullptr)
	{
		if (LastHoverActor != CurHoverActor)
		{
			LastHoverActor.GetInterface()->UnHighlightActor();
			if (CurHoverActor != nullptr)
			{
				CurHoverActor.GetInterface()->HighlightActor();
			}
		}
	}
	else
	{
		if (CurHoverActor != nullptr)
		{
			CurHoverActor.GetInterface()->HighlightActor();
		}
	}
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (APawn* TargetPawn = GetPawn<APawn>())
	{
		const FVector2D InputAxisVec = InputActionValue.Get<FVector2D>();
		const FRotator  Rotation     = GetControlRotation();
		const FRotator  YawRotation(0, Rotation.Yaw, 0);

		FRotationMatrix YawMatrix  = FRotationMatrix(YawRotation);
		const FVector   ForwardDir = YawMatrix.GetUnitAxis(EAxis::X);
		const FVector   RightDir   = YawMatrix.GetUnitAxis(EAxis::Y);

		TargetPawn->AddMovementInput(ForwardDir, InputAxisVec.X);
		TargetPawn->AddMovementInput(RightDir, InputAxisVec.Y);
	}
}

void AAuraPlayerController::AbilityInputPressed(EAuraInputTypes InType)
{
	if (InType == EAuraInputTypes::LeftMouseBtn)
	{
		bTargeting = CurHoverActor != nullptr;
		if (bTargeting)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::AbilityInputReleased(EAuraInputTypes InType)
{
	if (InType == EAuraInputTypes::LeftMouseBtn)
	{
		if (bTargeting)
		{
			if (GetASC())
			{
				auto InTag = FAuraGASEnumManager::GetInputGameplayTagByEnum(InType);
				GetASC()->AbilityInputReleased(InTag);
			}
		}
		else
		{
			if (LMBPressedTime <= ShortPressTimeThreshold)
			{
				if (APawn* TargetPawn = GetPawn())
				{
					UNavigationPath* TargetNavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
						this,
						TargetPawn->GetActorLocation(),
						CachedDestination
					);
					if (TargetNavPath && TargetNavPath->PathPoints.Num() > 0)
					{
						SplineComponent->ClearSplinePoints();
						for (const FVector& Point : TargetNavPath->PathPoints)
						{
							SplineComponent->AddSplinePoint(Point, ESplineCoordinateSpace::World);
						}
						CachedDestination = TargetNavPath->PathPoints.Last();
						bAutoRunning      = true;
					}
					else
					{
						bAutoRunning = false;
					}
				}
			}

			LMBPressedTime = 0;
			bTargeting     = false;
		}
		return;
	}
	if (GetASC())
	{
		auto InTag = FAuraGASEnumManager::GetInputGameplayTagByEnum(InType);
		GetASC()->AbilityInputReleased(InTag);
	}
}

void AAuraPlayerController::AbilityInputHeld(EAuraInputTypes InType)
{
	if (InType != EAuraInputTypes::LeftMouseBtn)
	{
		if (GetASC())
		{
			auto InTag = FAuraGASEnumManager::GetInputGameplayTagByEnum(InType);
			GetASC()->AbilityInputHeld(InTag);
		}
	}
	else if (bTargeting)
	{
		if (GetASC())
		{
			auto InTag = FAuraGASEnumManager::GetInputGameplayTagByEnum(InType);
			GetASC()->AbilityInputHeld(InTag);
		}
	}
	else
	{
		bAutoRunning   = false;
		LMBPressedTime += GetWorld()->DeltaTimeSeconds;

		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
		{
			CachedDestination = HitResult.ImpactPoint;
		}

		if (APawn* TargetPawn = GetPawn())
		{
			const FVector WorldDirNormal = (CachedDestination - TargetPawn->GetActorLocation()).GetSafeNormal();
			TargetPawn->AddMovementInput(WorldDirNormal);
		}
	}
}
