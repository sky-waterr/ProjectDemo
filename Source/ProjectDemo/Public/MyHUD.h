// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/UniformGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "../HUD/ItemUniformGridPanel.h"
#include "../HUD/ItemWidget.h"
#include "MyHUD.generated.h"

class UMainWidget;
class AMyPlayerController;
/**
 *
 */
UCLASS()
class PROJECTDEMO_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    // 显示交互按钮
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowInteractBtn(const bool& flag);
    // 显示交互对话框
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnTalkBtnClicked();
    void ShowInteractTalk(const bool& flag);
    // 提示道具的获取或者数据的获取
    void AddPopupInfo(const FString &info);
    // 触发动作按钮
    void SlotOnPressTalkBtn();
    // 触发属性窗口
    void SlotOnPropertyBtn();
    // 触发显示商店窗口
    void SlotOnShopBtn();
    // 触发商店购买按钮
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnBuyBtnClicked();
    // 触发关闭商店按钮
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnCloseBtnClicked();
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnNpcInteractEnd();

protected:
    virtual void BeginPlay() override;

private:
    // 初始化各个控件的绑定函数
    void InitCompFunc();
    void SetItemBox(TObjectPtr<UItemUniformGridPanel> itemBox, TSubclassOf<UItemWidget> itemClass, TObjectPtr<AMyPlayerController> controller);
    void ShowMainWidget();
    void ShowShopWidget();
    void ChangeItemBoxState(const TObjectPtr<AMyPlayerController> controller);

private:
    // 用于蓝图设置mainwidget的实例
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<UMainWidget> m_mainWidgetClass;

    // 保存mainwidget实例，给后续调用
    UPROPERTY()
    TObjectPtr<UMainWidget> m_mainWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> m_shopWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> m_propertyWidget;

    TArray<FString> m_lineArray;
    int32 m_curLineIndex;
    TMap<FString, FItemTableRow> m_itemMap;
    NpcType m_npcType;
};
