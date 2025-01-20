// Fill out your copyright notice in the Description page of Project Settings.


#include "My2dPawn.h"

// Sets default values
AMy2dPawn::AMy2dPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMy2dPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMy2dPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMy2dPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

