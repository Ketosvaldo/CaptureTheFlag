// Fill out your copyright notice in the Description page of Project Settings.


#include "Boomerang.h"


// Sets default values
ABoomerang::ABoomerang()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MeshComponent->SetupAttachment(BoxCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Counter = 0;
}

void ABoomerang::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoomerang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator ActorRotation = MeshComponent->GetComponentRotation();
	ActorRotation.Add(0.f, 20.f, 0.f);
	SetActorRotation(ActorRotation);

	if(bReverse)
	{
		GoingReverse();
		return;
	}

	Counter += DeltaTime;
	if(Counter >= 2.f)
	{
		bReverse = true;
	}
}

void ABoomerang::GoingReverse()
{
	const FVector ActorLocation = GetActorLocation();
	const FVector InstigatorLocation = GetInstigator()->GetActorLocation();
	const FVector Velocity = FVector(InstigatorLocation - ActorLocation).GetSafeNormal();
	ProjectileMovement->Velocity = Velocity * 800.f;
}

