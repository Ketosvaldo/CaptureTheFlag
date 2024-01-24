// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

#include "Kismet/GameplayStatics.h"

AGrenade::AGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	MeshComponent->SetupAttachment(RootComponent);

	const FString SoundPath = TEXT("/Game/StarterContent/Audio/Explosion01.Explosion01");
	ExplosionSound = LoadObject<USoundBase>(nullptr, *SoundPath);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 200.f;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));
	RadialForce->SetupAttachment(MeshComponent);
	RadialForce->SetWorldLocation(MeshComponent->GetComponentLocation());
	RadialForce->Radius = 500.f;
	RadialForce->ImpulseStrength = 200000.0f;

	Counter = 0;
	HealthTime = 5.0f;
	Damage = 100.0f;
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Counter += DeltaTime;
	if(Counter >= HealthTime)
	{
		const UWorld* World = GetWorld();
		UGameplayStatics::ApplyRadialDamage(World, RadialForce->ImpulseStrength, GetActorLocation(), RadialForce->Radius, nullptr, IgnoreActors);
		RadialForce->FireImpulse();
		UGameplayStatics::SpawnSound2D(World, ExplosionSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);
		Destroy();
	}
}