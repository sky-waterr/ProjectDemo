// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueComponent.h"
#include "../Public/MyHUD.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
    : m_lineArray()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

TArray<FString>& UDialogueComponent::GetNpcLineArray()
{
    return m_lineArray;
}

NpcType UDialogueComponent::GetNpcType()
{
    return m_npcType;
}

// Called when the game starts
void UDialogueComponent::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

