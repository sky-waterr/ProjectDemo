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
    FString Speaker;  // ˭˵�ģ������� NPC ����ң�

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Line;  // �Ի�����
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
    // ��ȡ-��ǰNPC�ĶԻ�������
    UFUNCTION(BlueprintCallable, Category = "NPC Component")
    TArray<FString>& GetNpcLineArray();
    // ��ȡ-NPC��־λ
    NpcType GetNpcType();
protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
    TArray<FString> m_lineArray;                   // ��ǰ�Ի��ı�ǩ��

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
    NpcType m_npcType;                   // ��ǰ�Ի��ı�ǩ��
};
