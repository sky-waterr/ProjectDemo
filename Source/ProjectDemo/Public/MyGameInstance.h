// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Struct/Weapon.h"
#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PROJECTDEMO_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UMyGameInstance();

    FItemTableRow* GetItemStruct(const FString& lineIndex);

private:
    TMap<FString, FItemTableRow*> m_itemTableMap;
};
