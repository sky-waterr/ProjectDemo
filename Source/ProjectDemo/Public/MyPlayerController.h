// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyHUD.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
/**
 *
 */
UCLASS()
class PROJECTDEMO_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void OnMove(const FInputActionValue& value);
    void OnInterBtnPress(const FInputActionValue& value);
    void OnPropertyBtnClicked(const FInputActionValue& value);
    // �������������龰
    void SetDefaultBind();
    // ���öԻ��龰��ֻ�ſ�E����������������������
    void SetDialogueBind();
    // ��յ�ǰ�Ĳ�����
    void ClearInputBinds();
    // ��ȡ��ǰ�趨����ҵ�������
    UFUNCTION(BlueprintCallable, Category = "PlayerNumb")
    int GetCurPlayerItemMax();
    // ���õ�ǰ�趨����ҵ�������
    UFUNCTION(BlueprintCallable, Category = "PlayerNumb")
    void SetCurPlayerItemMax(const int numb);
    // ��ǰ��һ�ȡ�ĵ���
    void PlayerGetItem(const FString& itemStr, const int numb);
    // ��ǰ���ʧȥ����
    void PlayerLostItem(const FString& itemStr, const int numb);
    // ��ȡ-��ǰ�����������Npc
    TArray<AActor*> GetTouchedNpcs();
    // ��ȡ-��ұ����ڵĵ���
    TMap<FString, FItemTableRow> GetPlayerBackageItems();
    // ��ȡ-��ҷ�Χ��Npc��ItemData��DialogueData
    TMap<FString, FItemTableRow> GetTouchedNpcItems();
    // ��ȡ-��ҷ�Χ��Npc�ĶԻ����ݺ�Npc��־λ
    void GetTouchedNpcDialogueData(TArray<FString>& outLineData, NpcType outNpcFlag);
    // ��ȡ-��ҷ�Χ��Npc��ItemData��DialogueData
    void GetTouchedNpcAllData(TMap<FString, FItemTableRow>& outItems, TArray<FString>& outDialogues, NpcType& outNpcType);

public:
    UPROPERTY()
    TObjectPtr<AMyHUD> m_hud;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> playerInputMapping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> myMoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> myInteraction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> m_propertyAct;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    int m_dircX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerInput", meta = (AllowPrivateAccess = "true"))
    int m_dircY;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerItemNumb", meta = (AllowPrivateAccess = "true"))
    int m_playerItemNumb;

protected:
    // ��д Init ����
    AMyPlayerController();
    virtual void BeginPlay() override;
};
