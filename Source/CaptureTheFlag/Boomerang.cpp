// Fill out your copyright notice in the Description page of Project Settings.


#include "Boomerang.h"


// Sets default values
ABoomerang::ABoomerang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MeshComponent->SetupAttachment(BoxCollision);
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
}

