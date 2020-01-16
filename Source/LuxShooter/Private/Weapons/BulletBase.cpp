#include "Weapons/BulletBase.h"
#include "Weapons/WeaponsBase.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	SetRootComponent(HitSphere);

	HitSphere->InitSphereRadius(12.F);
	HitSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	HitSphere->SetNotifyRigidBodyCollision(true);

	//Creates the projectile
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(HitSphere);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Default checks
	if (GetOwner())
		MeshComponent->IgnoreActorWhenMoving(GetOwner(), true);

	if (GetOwner() && GetOwner()->GetOwner())
		MeshComponent->IgnoreActorWhenMoving(GetOwner()->GetOwner(), true);

	//Movement
	ProjectileMovemntComponent = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("ProjectileMovement"));
	ProjectileMovemntComponent->InitialSpeed = 3000;
	ProjectileMovemntComponent->Velocity = FVector(1.F, 0.F, 0.F);
}

void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
	HitSphere->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
}

void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::OnHit(UPrimitiveComponent* OnComponentHit, UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
		return;

	AWeaponsBase* MyWeapon = Cast<AWeaponsBase>(GetOwner());

	float DamageToDeal;

	if (MyWeapon)
		DamageToDeal = MyWeapon->Damage;

	else
		DamageToDeal = 50.F;

	float DamageMultiplier = 1.F;

	if (Hit.BoneName == TEXT("Head"))
		DamageMultiplier = 2.F;

	const float FinalDamage = DamageToDeal * DamageMultiplier;

	UGameplayStatics::ApplyDamage(OtherActor, FinalDamage, nullptr, GetOwner(),
		UDamageType::StaticClass());

	
}

