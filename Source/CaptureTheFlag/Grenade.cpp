// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"
#include "Kismet/GameplayStatics.h"

AGrenade::AGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	const FString MeshPath = TEXT("/Game/Models/Grenade.Grenade");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	
	const FString SoundPath = TEXT("/Game/StarterContent/Audio/Explosion01.Explosion01");
	ExplosionSound = LoadObject<USoundBase>(nullptr, *SoundPath);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1800.f;
	ProjectileMovement->ProjectileGravityScale = 1.f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereComponent->SetupAttachment(MeshComponent);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->SetSphereRadius(30.f);
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenade::Explode()
{
	const UWorld* World = GetWorld();
	UGameplayStatics::SpawnSound2D(World, ExplosionSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);
	//Destroy();
}