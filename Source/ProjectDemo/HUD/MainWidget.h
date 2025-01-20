// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include "MainWidget.generated.h"

class UScrollBox;
class UOverlay;
class UButton;
/**
 *
 */
UCLASS()
class PROJECTDEMO_API UMainWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // 提示道具的获取或者数据的获取
    void AddPopupInfo(const FString& info);
    // 显示交互按钮
    void ShowInteractBtn(const ESlateVisibility& flag);
    // 显示交互对话框
    void ShowInteractTalk(const ESlateVisibility& flag);
    void SetInteractText(const FString& text);
    ESlateVisibility GetInteractBtnState();

public:
    // 右侧的消息滚动窗口
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UScrollBox> m_scrollBox;

    // 右下角的交互按钮
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UButton> m_interactBtn;

    // 正下方的交互对话框
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UTextBlock> m_interactText;
    // 正下方的交互对话框的背景模糊
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UBackgroundBlur> m_textBlur;
};
