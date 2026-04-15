// Copyright NineForce Entertainment

#include "Player/AuraPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetControlRotation(FRotator::ZeroRotator);

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
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
