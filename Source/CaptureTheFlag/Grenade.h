// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Grenade.generated.h"

UCLASS()
class CAPTURETHEFLAG_API AGrenade : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ExplosionParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* RadialForce;
	
public:	
	// Sets default values for this actor's properties
	AGrenade();
	float Damage;

protected:
	float Counter;
	float HealthTime;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AActor*> IgnoreActors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
