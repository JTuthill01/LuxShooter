#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuxCharacterBase.generated.h"

class UCameraComponent;
class AWeaponsBase;

UCLASS()
class LUXSHOOTER_API ALuxCharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Character", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

public:
	// Sets default values for this character's properties
	ALuxCharacterBase();

	UCameraComponent* GetCamera() { return CameraComponent; }

	USkeletalMeshComponent* GetMesh1P() { return Mesh1P; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void Turn(float Value);
	void TurnRate(float Value);
	void LookUp(float Value);
	void LookUpRate(float Value);

	void StartJump();
	void StopJump();
	void StartShoot();
	void StopShoot();
	void StartSprint();
	void StopSprint();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lux")
	float BaseTurnRate = 45.F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lux")
	float BaseLookAtRate = 45.F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lux")
	float MaxSprintSpeed = 900.F;

private:
	float DefaultWalkSpeed;

	AWeaponsBase* EquippedWeapon;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	FName AttachSocket;

	UFUNCTION(BlueprintPure, Category = "Weapons") //Pure means no pin in blueprint
	AWeaponsBase* GetEquippedWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	AWeaponsBase* EquipWeapon(TSubclassOf<AWeaponsBase> NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void UnEquipWeapon();
};
