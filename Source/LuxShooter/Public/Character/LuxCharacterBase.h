// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuxCharacterBase.generated.h"

class UCameraComponent;

UCLASS()
class LUXSHOOTER_API ALuxCharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

public:
	// Sets default values for this character's properties
	ALuxCharacterBase();

	//Getters
	UCameraComponent* GetCameraComponent() { return CameraComponent; }
	USkeletalMeshComponent* GetMesh1P() { return Mesh1P; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Delta);
	void MoveRight(float Delta);
	void MoveUp(float Delta);
	void Turn(float Delta);
	void TurnRate(float Delta);
	void LookUp(float Delta);
	void LookUpRate(float Delta);

	void StartJump();
	void StopJump();
	void StartShoot();
	void StopShoot();
	void StartSprint();
	void StopSprint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseTurnRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseLookAtRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.F;

private:
	AWeaponBase* EquippedWeapon;

	float DefaultWalkSpeed;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName AttachSocket;

	UFUNCTION(BlueprintPure, Category = "Weapon") //Pure means no pin in blueprint
	AWeaponBase* GetEquippedWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnequipWeapon();
};
