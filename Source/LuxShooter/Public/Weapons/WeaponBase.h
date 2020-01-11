#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class ABulletBase;

UCLASS()
class LUXSHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* MuzzlePoint;
	
public:	
	AWeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABulletBase> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float RefireRate = 0.1F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int RemainingAmmo = 9999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bFullyAutomatic = false;

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void StartFiring();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void StopFiring();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") //Exposes to BP as a event, no code function
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") //Exposes to BP as a event, no code function
	void OnUnequiped();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void FireRound();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle RefireHandle;
};
