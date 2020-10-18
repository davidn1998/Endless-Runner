// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"

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
		return;
	}

	CurrentLane = (LevelManager->GetNumberOfLanes() / 2) + 1;
	LaneWidth = LevelManager->GetLaneWidth();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &APlayerPawn::MoveLeft);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &APlayerPawn::MoveRight);
}

void APlayerPawn::MoveLeft()
{
	if (CurrentLane <= 1 || bMoving)
	{
		return;
	}

	bMoving = true;
	float TargetY = GetActorLocation().Y - LaneWidth;
	TargetLocation = FVector(GetActorLocation().X, TargetY, GetActorLocation().Z);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);

		CurveTimeline.PlayFromStart();

		FOnTimelineEvent TimeLineFinished;
		TimeLineFinished.BindUFunction(this, FName("ResetMovement"));
		CurveTimeline.SetTimelineFinishedFunc(TimeLineFinished);
	}

	CurrentLane--;
}

void APlayerPawn::MoveRight()
{
	if (CurrentLane >= LevelManager->GetNumberOfLanes() || bMoving)
	{
		return;
	}

	bMoving = true;
	float TargetY = GetActorLocation().Y + LaneWidth;
	TargetLocation = FVector(GetActorLocation().X, TargetY, GetActorLocation().Z);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);

		CurveTimeline.PlayFromStart();

		FOnTimelineEvent TimeLineFinished;
		TimeLineFinished.BindUFunction(this, FName("ResetMovement"));
		CurveTimeline.SetTimelineFinishedFunc(TimeLineFinished);
	}

	CurrentLane++;
}

void APlayerPawn::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(GetActorLocation(), TargetLocation, Value);
	SetActorLocation(NewLocation);
}

void APlayerPawn::ResetMovement()
{
	bMoving = false;
}
