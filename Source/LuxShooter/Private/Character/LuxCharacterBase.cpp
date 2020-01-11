// Fill out your copyright notice in the Description page of Project Settings.
#include "LuxCharacterBase.h"
#include "Weapons/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ALuxCharacterBase::ALuxCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(CameraComponent);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(false);
	Mesh1P->SetCastShadow(false);
	Mesh1P->SetReceivesDecals(false);

	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void ALuxCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void ALuxCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALuxCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Input
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ALuxCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ALuxCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &ALuxCharacterBase::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ALuxCharacterBase::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ALuxCharacterBase::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ALuxCharacterBase::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ALuxCharacterBase::LookUpRate);

	//Jump
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ALuxCharacterBase::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ALuxCharacterBase::StopJump);

	//Shoot
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ALuxCharacterBase::StartShoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &ALuxCharacterBase::StopShoot);

	//Sprinting 
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ALuxCharacterBase::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ALuxCharacterBase::StopSprint);
}

void ALuxCharacterBase::MoveForward(float Delta)
{
	if (Delta != 0.F)
		AddMovementInput(GetActorForwardVector(), Delta);

	else
		StopSprint();
}

void ALuxCharacterBase::MoveRight(float Delta)
{
	if (Delta != 0.F)
		AddMovementInput(GetActorRightVector(), Delta);
}

void ALuxCharacterBase::MoveUp(float Delta)
{
	if (Delta != 0.F)
		AddMovementInput(GetActorUpVector(), Delta);
}

void ALuxCharacterBase::Turn(float Delta)
{
	AddControllerYawInput(Delta);
}

void ALuxCharacterBase::TurnRate(float Delta)
{
	AddControllerYawInput(Delta * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALuxCharacterBase::LookUp(float Delta)
{
	AddControllerPitchInput(Delta);
}

void ALuxCharacterBase::LookUpRate(float Delta)
{
	AddControllerPitchInput(Delta * BaseLookAtRate * GetWorld()->GetDeltaSeconds());
}

void ALuxCharacterBase::StartJump()
{
	Jump();
}

void ALuxCharacterBase::StopJump()
{
	StopJumping();
}

void ALuxCharacterBase::StartShoot()
{
	if (EquippedWeapon)
		EquippedWeapon->StartFiring();
}

void ALuxCharacterBase::StopShoot()
{
	if (EquippedWeapon)
		EquippedWeapon->StopFiring();
}

void ALuxCharacterBase::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void ALuxCharacterBase::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

AWeaponBase* ALuxCharacterBase::GetEquippedWeapon()
{
	return EquippedWeapon;
}

AWeaponBase* ALuxCharacterBase::EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon)
{
	if (EquippedWeapon)
		UnequipWeapon();

	FActorSpawnParameters Parms;
	Parms.Owner = this;
	Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(NewWeapon, Parms);
	EquippedWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocket);

	return EquippedWeapon;
}

void ALuxCharacterBase::UnequipWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->OnUnequiped();
		EquippedWeapon->Destroy();
	}
}

