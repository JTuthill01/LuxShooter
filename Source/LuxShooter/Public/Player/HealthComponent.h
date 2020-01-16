#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

class UDamageType;
class AController;
class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUXSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	float CurrentHealth;

	UFUNCTION()
	void OnOwnerTakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);

public:	
	UHealthComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float StartingHealth;

	UFUNCTION(BlueprintPure, Category = "Health") //Pure means no pin in blueprint
	float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "Health") //Pure means no pin in blueprint
	bool GetIsDead();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDied OnDied;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

};
