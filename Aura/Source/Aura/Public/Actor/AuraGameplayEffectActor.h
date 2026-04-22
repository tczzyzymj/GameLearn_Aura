// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraGameplayEffectActor.generated.h"

class UGameplayEffect;
struct FActiveGameplayEffectHandle;

UENUM(BlueprintType)
enum class EGameplayEffectAddPolicy : uint8
{
	OnBeginOverlap,
	OnEndOverlap,
	OnStayForSpecificTime,
};

UENUM(BlueprintType)
enum class EGameplayEffectRemovePolicy : uint8
{
	Never,
	OnEndOverlap,
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameplayEffectAddPolicy AddPolicy = EGameplayEffectAddPolicy::OnBeginOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameplayEffectRemovePolicy RemovePolicy = EGameplayEffectRemovePolicy::OnEndOverlap;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		meta = (EditCondition = "AddPolicy == EGameplayEffectAddPolicy::OnStayForSpecificTime", EditConditionHides)
	)
	float StayTimeToAdd = 0;
};

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

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Destroyed() override;

	void InternalTickForStayGameplayEffect(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToActor(AActor* InTargetActor, const FAuraGameplayEffectData& InAuraGameplayEffectData);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* InTargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* InTargetActor);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura GAS")
	TArray<FAuraGameplayEffectData> GameplayEffectDataArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura GAS")
	float Level = 1;

	TMap<TObjectPtr<AActor>, TArray<FActiveGameplayEffectHandle>> ActorInfinityGameplayEffectMap;

	TMap<TObjectPtr<AActor>, TArray<FAuraGameplayEffectData>> ActorStayTimeMap;

	// A temp array to remove keys from ActorStayTimeMap
	TArray<TObjectPtr<AActor>> ActorStayTimeToRemove;
};
