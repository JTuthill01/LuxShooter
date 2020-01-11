#include "Weapons/WeaponBase.h"
#include "Weapons/BulletBase.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

AWeaponBase::AWeaponBase() : BulletClass(ABulletBase::StaticClass())
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MuzzlePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	MuzzlePoint->SetupAttachment(RootComp);
	MuzzlePoint->ArrowSize = 0.25F;
	MuzzlePoint->ArrowColor = FColor::Green;
}

void AWeaponBase::StartFiring_Implementation()
{
	if (!BulletClass)
		return;

	if (bFullyAutomatic)
	{
		GetWorldTimerManager().SetTimer(RefireHandle, this, &AWeaponBase::FireRound, RefireRate, true);

		FireRound();
	}

	else
	{
		FireRound();

		UE_LOG(LogTemp, Warning, TEXT("Called"));
	}
}

void AWeaponBase::StopFiring_Implementation()
{
	GetWorldTimerManager().ClearTimer(RefireHandle);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::FireRound_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Called"));

	if (RemainingAmmo > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Called on IF statement"));

		RemainingAmmo--;

		AActor* BulletOwner = this;

		const FTransform SpawnTransform = MuzzlePoint->GetComponentTransform();

		FActorSpawnParameters Parms;
		Parms.Owner = BulletOwner;
		Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(BulletClass, SpawnTransform, Parms);
	}
}
