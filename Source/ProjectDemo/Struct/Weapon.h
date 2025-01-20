// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"    // 引入 UTexture2D
#include "Engine/StaticMesh.h"   // 引入 UStaticMesh
#include "Engine/DataTable.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class JobType : uint8
{
    Warrior UMETA(DisplayName = "Warrior"),
    Mage UMETA(DisplayName = "Mage"),
    Healer UMETA(DisplayName = "Healer")
};

UENUM(BlueprintType)
enum class ItemType : uint8
{
    EQUIP UMETA(DisplayName = "EQUIP"),
    PROP UMETA(DisplayName = "PROP")
};

UENUM(BlueprintType)
enum class NpcType : uint8
{
    SHOP UMETA(DisplayName = "SHOP"),
    ENEMY UMETA(DisplayName = "ENEMY"),
    ITEMBOX UMETA(DisplayName = "ITEMBOX"),
    OTHER UMETA(DisplayName = "OTHER")
};

USTRUCT(BlueprintType)
struct FItemTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "name"))
    FString name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "itemType"))
    ItemType itemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "damage"))
    int32 damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "damageFloat"))
    float damageFloat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "icon"))
    TObjectPtr<UTexture2D> icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "model"))
    TObjectPtr<UStaticMesh> model;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "jobType"))
    JobType jobType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "count"))
    int32 count;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "description"))
    FString description;
};
