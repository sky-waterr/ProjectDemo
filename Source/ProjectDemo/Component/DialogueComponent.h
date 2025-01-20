// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Struct/Weapon.h"
#include "DialogueComponent.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLine
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Speaker;  // 谁说的（可以是 NPC 或玩家）

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Line;  // 对话内容
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTDEMO_API UDialogueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    // Sets default values for this component's properties
    UDialogueComponent();
    // 获取-当前NPC的对话数据组
    UFUNCTION(BlueprintCallable, Category = "NPC Component")
    TArray<FString>& GetNpcLineArray();
    // 获取-NPC标志位
    NpcType GetNpcType();
protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
    TArray<FString> m_lineArray;                   // 当前对话的标签号

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
    NpcType m_npcType;                   // 当前对话的标签号
};
