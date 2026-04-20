// Copyright NineForce Entertainment

#include "AbilitySystem/ModMagCalc/MMC_MaxHealthPoint.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/AuraCombatInterface.h"

UMMC_MaxHealthPoint::UMMC_MaxHealthPoint()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot          = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealthPoint::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer*  SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*  TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	float TargetVigorValue        = 0.0f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, TargetVigorValue);
	TargetVigorValue                      = FMath::Max<float>(TargetVigorValue, 0.0f);
	IAuraCombatInterface* TargetInterface = Cast<IAuraCombatInterface>(Spec.GetContext().GetSourceObject());
	auto                  TargetLevel     = TargetInterface->GetCharacterLevel();
	float                 MaxHealthPoint  = 80.f + 5 * TargetVigorValue + 15 * TargetLevel;
	return MaxHealthPoint;
}
