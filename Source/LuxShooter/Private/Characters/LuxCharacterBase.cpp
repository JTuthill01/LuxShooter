#include "LuxCharacterBase.h"
#include "Weapons/WeaponsBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALuxCharacterBase::ALuxCharacterBase()
{
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

	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ALuxCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ALuxCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &ALuxCharacterBase::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ALuxCharacterBase::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ALuxCharacterBase::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ALuxCharacterBase::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ALuxCharacterBase::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ALuxCharacterBase::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ALuxCharacterBase::StopJump);
	
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ALuxCharacterBase::StartShoot);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ALuxCharacterBase::StopShoot);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ALuxCharacterBase::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ALuxCharacterBase::StopSprint);
}

void ALuxCharacterBase::MoveForward(float Value)
{
	if (Value != 0.F)
		AddMovementInput(GetActorForwardVector(), Value);

	else
		StopSprint();
}

void ALuxCharacterBase::MoveRight(float Value)
{
	if (Value != 0.F)
		AddMovementInput(GetActorRightVector(), Value);
}

void ALuxCharacterBase::MoveUp(float Value)
{
	if (Value != 0.F)
		AddMovementInput(GetActorUpVector(), Value);
}

void ALuxCharacterBase::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ALuxCharacterBase::TurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALuxCharacterBase::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ALuxCharacterBase::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookAtRate * GetWorld()->GetDeltaSeconds());
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

AWeaponsBase* ALuxCharacterBase::GetEquippedWeapon()
{
	return EquippedWeapon;
}

AWeaponsBase* ALuxCharacterBase::EquipWeapon(TSubclassOf<AWeaponsBase> NewWeapon)
{
	if (EquippedWeapon)
		UnEquipWeapon();

	FActorSpawnParameters Parms;
	Parms.Owner = this;
	Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EquippedWeapon = GetWorld()->SpawnActor<AWeaponsBase>(NewWeapon, Parms);

	EquippedWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, 
		AttachSocket);

	return EquippedWeapon;
}

void ALuxCharacterBase::UnEquipWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->OnUnEquipped();
	}
}
