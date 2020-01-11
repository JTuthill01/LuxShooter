// Fill out your copyright notice in the Description page of Project Settings.
#include "HealthComponent.h"
#include "GameFramework/Actor.h"

void UHealthComponent::OnOwnerTakenDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = CurrentHealth - Damage;

	CurrentHealth = FMath::Clamp<float>(CurrentHealth, 0.F, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);

	if (GetIsDead())
		OnDied.Broadcast();
}

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


float UHealthComponent::GetCurrentHealth() { return CurrentHealth; }

bool UHealthComponent::GetIsDead() { return CurrentHealth <= 0.F; }

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingHealth = StartingHealth == 0 ? MaxHealth : StartingHealth;

	CurrentHealth = StartingHealth;

	if (GetOwner())
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerTakenDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

