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
    // ��ʾ���ߵĻ�ȡ�������ݵĻ�ȡ
    void AddPopupInfo(const FString& info);
    // ��ʾ������ť
    void ShowInteractBtn(const ESlateVisibility& flag);
    // ��ʾ�����Ի���
    void ShowInteractTalk(const ESlateVisibility& flag);
    void SetInteractText(const FString& text);
    ESlateVisibility GetInteractBtnState();

public:
    // �Ҳ����Ϣ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UScrollBox> m_scrollBox;

    // ���½ǵĽ�����ť
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UButton> m_interactBtn;

    // ���·��Ľ����Ի���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UTextBlock> m_interactText;
    // ���·��Ľ����Ի���ı���ģ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyWidget", meta = (BindWidget))
    TObjectPtr<UBackgroundBlur> m_textBlur;
};
