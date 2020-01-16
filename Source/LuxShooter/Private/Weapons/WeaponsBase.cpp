#include "Weapons/WeaponsBase.h"
#include "Weapons/BulletBase.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"

AWeaponsBase::AWeaponsBase() : BulletClass(ABulletBase::StaticClass())
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MuzzlePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	MuzzlePoint->SetupAttachment(RootComp);
	MuzzlePoint->ArrowSize = 0.25F;
	MuzzlePoint->ArrowColor = FColor::Green;
}

void AWeaponsBase::StartFiring_Implementation()
{
	if (!BulletClass)
		UE_LOG(LogTemp, Fatal, TEXT("Bullet Failed!!!"));

	if(BulletClass)
		UE_LOG(LogTemp, Warning, TEXT("Bullet Succeed"));

	
	if (bIsFullyAutomatic)
	{
		GetWorldTimerManager().SetTimer(RefireHandle, this, &AWeaponsBase::FireRound,
			RefireRate, true);

		FireRound();
	}

	else
		FireRound();
}

void AWeaponsBase::StopFiring_Implementation()
{
	GetWorldTimerManager().ClearTimer(RefireHandle);
}

// Called when the game starts or when spawned
void AWeaponsBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponsBase::FireRound_Implementation()
{
	if (RemainingAmmo > 0)
	{
		RemainingAmmo--;
		AActor* BulletOwner = this;
		FTransform SpawnTransform = MuzzlePoint->GetComponentTransform();

		FActorSpawnParameters Parms;
		Parms.Owner = BulletOwner;
		Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(BulletClass, SpawnTransform, Parms);;
	}
}