#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponsBase.generated.h"

class ABulletBase;

UCLASS()
class LUXSHOOTER_API AWeaponsBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootComp;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* MuzzlePoint;

public:	
	// Sets default values for this actor's properties
	AWeaponsBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	TSubclassOf<ABulletBase> BulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	float RefireRate = 0.1F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	float Damage = 20.F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	bool bIsFullyAutomatic = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	int RemainingAmmo = 9999;

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon") 
	void StartFiring();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon") 
	void StopFiring();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") 
	void OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") //Exposes to BP as a event, no code function
	void OnUnEquipped();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon") 
	void FireRound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle RefireHandle;
};
