// Copyright NineForce Entertainment

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(MeshComponent);
}

void AAuraEffectActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherOverlappedComponent,
	int32                OtherBodyIndex,
	bool                 bFromSweep,
	const FHitResult&    SweepResult
)
{
	// TODO : temp code , delete later
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		if (auto AbilityComponent = ASCInterface->GetAbilitySystemComponent())
		{
			auto               AttributeSet = Cast<UAuraAttributeSet>(AbilityComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
			UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
			MutableAttributeSet->SetHealthPoint(MutableAttributeSet->GetHealthPoint() + 50);

			MutableAttributeSet->SetManaPoint(MutableAttributeSet->GetManaPoint() + 50);
			Destroy();
		}
	}
}

void AAuraEffectActor::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherComp,
	int32                OtherBodyIndex
)
{
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

// Called every frame
void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
