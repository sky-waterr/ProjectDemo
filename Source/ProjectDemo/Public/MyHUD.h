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
    // ��ʾ������ť
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowInteractBtn(const bool& flag);
    // ��ʾ�����Ի���
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnTalkBtnClicked();
    void ShowInteractTalk(const bool& flag);
    // ��ʾ���ߵĻ�ȡ�������ݵĻ�ȡ
    void AddPopupInfo(const FString &info);
    // ����������ť
    void SlotOnPressTalkBtn();
    // �������Դ���
    void SlotOnPropertyBtn();
    // ������ʾ�̵괰��
    void SlotOnShopBtn();
    // �����̵깺��ť
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnBuyBtnClicked();
    // �����ر��̵갴ť
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnCloseBtnClicked();
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void OnNpcInteractEnd();

protected:
    virtual void BeginPlay() override;

private:
    // ��ʼ�������ؼ��İ󶨺���
    void InitCompFunc();
    void SetItemBox(TObjectPtr<UItemUniformGridPanel> itemBox, TSubclassOf<UItemWidget> itemClass, TObjectPtr<AMyPlayerController> controller);
    void ShowMainWidget();
    void ShowShopWidget();
    void ChangeItemBoxState(const TObjectPtr<AMyPlayerController> controller);

private:
    // ������ͼ����mainwidget��ʵ��
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<UMainWidget> m_mainWidgetClass;

    // ����mainwidgetʵ��������������
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
