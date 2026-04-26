// Copyright NineForce Entertainment

#include "Actor/AuraProjectileActor.h"

// Sets default values
AAuraProjectileActor::AAuraProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent               = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 550;
	ProjectileMovementComponent->MaxSpeed = 550;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AAuraProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraProjectileActor::OnSphereOverlapped(
	UPrimitiveComponent* OverlappedComponent,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32                OtherBodyIndex,
	bool                 bFromSweep,
	const FHitResult&    SweepResult
)
{
}
