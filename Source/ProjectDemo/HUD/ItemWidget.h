// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Struct/Weapon.h"
#include "ItemWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTDEMO_API UItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

    // 这个方法会被用来更新 TextBlock 的文字并触发显示状态变化
    UFUNCTION(BlueprintCallable)
    void SetText(const FString& str);
    void SetImage(const TObjectPtr<UTexture2D> icon);
    // 设置-当前itemWidget的物品行号和物品信息
    void SetItemWidgetInfo(const FString& lineStr, const FItemTableRow& itemInfo);
    // 获取-当前itemWidget的物品行号和物品信息
    void GetItemWidgetInfo(FString& outLineStr, FItemTableRow& outItemInfo);
    // 获取-当前itemWidget的物品信息
    FItemTableRow& GetItemInfo();
    // 设置-当前的选中状态
    void SetClickedFlag(const bool flag);
    // 获取-当前的选中状态
    bool GetClickedFlag();
    // 清除-当前widget所有数据
    void ClearWidgetInfo();
    // 获取-当前物品对应的行号
    FString& GetLineStr();
    // 增减-当前物品的数量,增减后数量<=0,则此itemWidget清空所有数据
    void ChangeItemCount(const int32 numb);

protected:
    virtual void NativeConstruct() override;

    // 挂载的按钮触发函数
    UFUNCTION(BlueprintCallable, Category = "ItemWidget")
    void OnBtnClicked();

protected:
    // button的控件
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> m_itemBtn;

    // TextBlock 控件引用
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> m_numbText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> m_itemImage;

    UPROPERTY(meta = (BindWidget))
    bool m_isClicked;

private:
    FItemTableRow m_itemInfo;
    FString m_lineStr;
};
