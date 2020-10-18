// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ALevelManager::StaticClass(), FoundActors);
	LevelManager = Cast<ALevelManager>(FoundActors[0]);

	if (Cast<ALevelManager>(FoundActors[0]))
	{
		LevelManager = Cast<ALevelManager>(FoundActors[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Manager Found"));
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
