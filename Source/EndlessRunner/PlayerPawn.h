// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	int CurrentLane = 0;
	float LaneWidth;
	FVector TargetLocation;
	bool bMoving = false;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class ALevelManager *LevelManager;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category="Timeline")
	class UCurveFloat* CurveFloat;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void MoveLeft();
	UFUNCTION()
	void MoveRight();
	UFUNCTION()
	void TimelineProgress(float Value);
	// UFUNCTION()
	// void TimelineProgress(float Value);
	UFUNCTION()
	void ResetMovement();
};
