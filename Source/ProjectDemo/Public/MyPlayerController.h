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
    // 设置正常操作情景
    void SetDefaultBind();
    // 设置对话情景，只放开E按键互动，其它按键禁用
    void SetDialogueBind();
    // 清空当前的操作绑定
    void ClearInputBinds();
    // 获取当前设定的玩家道具总数
    UFUNCTION(BlueprintCallable, Category = "PlayerNumb")
    int GetCurPlayerItemMax();
    // 设置当前设定的玩家道具总数
    UFUNCTION(BlueprintCallable, Category = "PlayerNumb")
    void SetCurPlayerItemMax(const int numb);
    // 当前玩家获取的道具
    void PlayerGetItem(const FString& itemStr, const int numb);
    // 当前玩家失去道具
    void PlayerLostItem(const FString& itemStr, const int numb);
    // 获取-当前玩家碰触到的Npc
    TArray<AActor*> GetTouchedNpcs();
    // 获取-玩家背包内的道具
    TMap<FString, FItemTableRow> GetPlayerBackageItems();
    // 获取-玩家范围内Npc的ItemData和DialogueData
    TMap<FString, FItemTableRow> GetTouchedNpcItems();
    // 获取-玩家范围内Npc的对话数据和Npc标志位
    void GetTouchedNpcDialogueData(TArray<FString>& outLineData, NpcType outNpcFlag);
    // 获取-玩家范围内Npc的ItemData和DialogueData
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
    // 重写 Init 方法
    AMyPlayerController();
    virtual void BeginPlay() override;
};
