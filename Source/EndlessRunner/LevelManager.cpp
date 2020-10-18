// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelManager::ALevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LevelBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Level Bounds"));
	// LevelBounds->SetupAttachment(RootComponent);
	RootComponent = LevelBounds;
}

int ALevelManager::GetNumberOfLanes()
{
	return NumberOfLanes;
}

float ALevelManager::GetLaneWidth()
{
	return LaneWidth;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
