#include "HealthComponent.h"
#include "GameFramework/Actor.h"

void UHealthComponent::OnOwnerTakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = CurrentHealth - Damage;
	CurrentHealth = FMath::Clamp<float>(CurrentHealth, 0.F, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);

	if (GetIsDead())
		OnDied.Broadcast();
}

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

bool UHealthComponent::GetIsDead()
{
	return CurrentHealth <= 0.F;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingHealth == 0 ? MaxHealth : StartingHealth;

	CurrentHealth = StartingHealth;

	if (GetOwner())
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerTakenDamage);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

