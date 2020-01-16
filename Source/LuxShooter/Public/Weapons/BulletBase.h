#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class LUXSHOOTER_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", 
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet",
		meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovemntComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet",
		meta = (AllowPrivateAccess = "true"))
	USphereComponent* HitSphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "")
	float Damage = 30.F;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OnComponentHit, UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
