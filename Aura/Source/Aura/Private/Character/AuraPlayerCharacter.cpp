// Copyright NineForce Entertainment

#include "Character/AuraPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AuraGameDefine.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Public/Player/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraPlayerCharacter::AAuraPlayerCharacter()
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate              = FRotator(0.0f, 400.0f, 0.0f);
		MovementComponent->bConstrainToPlane         = true;
		MovementComponent->bSnapToPlaneAtStart       = true;

		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll  = false;
		bUseControllerRotationYaw   = false;
	}
}

void AAuraPlayerCharacter::InitAbilityActorInfo()
{
	auto TargetPlayerState = GetPlayerState<AAuraPlayerState>();
	check(TargetPlayerState);
	AbilitySystemComponent = TargetPlayerState->GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(TargetPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityInfoSet();
	AttributeSet = TargetPlayerState->GetAttributeSet();

	if (auto PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (auto TargetHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			TargetHUD->InitializeHUD(PlayerController, TargetPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitDefaultAttributes();

	// TMap<EAuraAttributeTypes, FGameplayAttribute> ResultMapData;
	// auto                                    TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	// for (TFieldIterator<FProperty> It(UAuraAttributeSet::StaticClass()); It; ++It)
	// {
	// 	FProperty* Property = *It;
	//
	// 	// 看是不是 struct
	// 	FStructProperty* StructProp = CastField<FStructProperty>(Property);
	// 	if (StructProp == nullptr)
	// 	{
	// 		continue;
	// 	}
	//
	// 	// 看这个 struct 是不是 FGameplayAttributeData
	// 	if (StructProp->Struct != TBaseStructure<FGameplayAttributeData>::Get())
	// 	{
	// 		continue;
	// 	}
	//
	// 	auto TargetIndex = TargetSEnum->GetValueByName(FName(StructProp->GetName()));
	// 	checkf(
	// 		TargetIndex != INDEX_NONE,
	// 		TEXT("Attribute 枚举和 AttributeSet 成员名字不匹配，成员名字:%s"),
	// 		*StructProp->Struct.GetName()
	// 	);
	//
	// 	ResultMapData.Add(static_cast<EAuraAttributeTypes>(TargetIndex), FGameplayAttribute(Property));
	// }
	//
	// for (const auto& Pair : ResultMapData)
	// {
	// 	FGameplayAttributeData* ValuePtr = Pair.Value.GetUProperty()->ContainerPtrToValuePtr<FGameplayAttributeData>(GetAttributeSet());
	// 	UE_LOG(
	// 		LogTemp,
	// 		Error,
	// 		TEXT("Attributes : %s, Value : %f"),
	// 		*Pair.Value.GetUProperty()->GetName(),
	// 		ValuePtr->GetCurrentValue()
	// 	);
	// }
}

// this is executed by server
void AAuraPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();

	AddCharacterAbilities();
}

void AAuraPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

int32 AAuraPlayerCharacter::GetCharacterLevel()
{
	auto TargetPlayerState = GetPlayerState<AAuraPlayerState>();
	check(TargetPlayerState);
	return TargetPlayerState->GetCharacterLevel();
}
