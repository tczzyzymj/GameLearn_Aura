// Copyright NineForce Entertainment

#include "AbilitySystem/ModMagCalc/MMC_MaxManaPoint.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/AuraCombatInterface.h"

UMMC_MaxManaPoint::UMMC_MaxManaPoint()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot          = false;
}

float UMMC_MaxManaPoint::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	float IntelligenceValue       = 0;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, IntelligenceValue);
	IntelligenceValue                     = FMath::Max<float>(IntelligenceValue, 0);
	IAuraCombatInterface* TargetInterface = Cast<IAuraCombatInterface>(Spec.GetContext().GetSourceObject());
	check(TargetInterface);
	int32 TargetLevel  = TargetInterface->GetCharacterLevel();
	float MaxManaPoint = 50.f + 10 * IntelligenceValue + 15 * TargetLevel;
	return MaxManaPoint;
}
