// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraGameplayEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraGameplayEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraGameplayEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToActor(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InEffectClass);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
