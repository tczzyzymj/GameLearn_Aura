// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AuraProjectileActor.generated.h"

UCLASS()
class AURA_API AAuraProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAuraProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnSphereOverlapped(
		UPrimitiveComponent* OverlappedComponent,
		AActor*              OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult&    SweepResult
	);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
};
