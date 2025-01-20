// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UMainWidget::AddPopupInfo(const FString& info)
{
    if (m_scrollBox != nullptr) {
        // 创建新的 TextBlock 用于显示消息
        UE_LOG(LogTemp, Warning, TEXT("AddPopupInfo 2 : %s"), *info);
        UTextBlock* textBlock = NewObject<UTextBlock>(this);
        textBlock->SetText(FText::FromString(info));

        m_scrollBox->AddChild(textBlock);
        m_scrollBox->ScrollToEnd();
    }
}

void UMainWidget::ShowInteractBtn(const ESlateVisibility& flag)
{
    if (m_interactBtn != nullptr) {
        m_interactBtn->SetVisibility(flag);
    }
}

void UMainWidget::ShowInteractTalk(const ESlateVisibility& flag)
{
    if (m_interactText != nullptr && m_textBlur != nullptr) {
        m_interactText->SetVisibility(flag);
        m_textBlur->SetVisibility(flag);
    }
}

void UMainWidget::SetInteractText(const FString& text)
{
    UE_LOG(LogTemp, Warning, TEXT("This is ShowInteractBtn.%s"), *text);
    if (m_interactText != nullptr) {
        m_interactText->SetText(FText::FromString(text));
    }
}

ESlateVisibility UMainWidget::GetInteractBtnState()
{
    return m_interactBtn->GetVisibility();
}
