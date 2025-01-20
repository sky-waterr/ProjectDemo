// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemWidget.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateTypes.h"
#include "Components/UniformGridPanel.h"

void UItemWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
    if (m_itemImage == nullptr || m_itemImage->GetBrush().GetResourceObject() == nullptr) {
        return;
    }
    Super::NativeTick(MyGeometry, DeltaTime);
}

void UItemWidget::SetText(const FString& str)
{
    if (m_numbText != nullptr && !str.IsEmpty() && str != "0") {
        m_numbText->SetText(FText::FromString(str));
        if (str == "1") {
            m_numbText->SetVisibility(ESlateVisibility::Hidden);
        } else {
            m_numbText->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UItemWidget::SetImage(const TObjectPtr<UTexture2D> icon)
{
    m_itemImage->SetBrushFromTexture(icon.Get());
}

void UItemWidget::SetItemWidgetInfo(const FString& lineStr, const FItemTableRow& itemInfo)
{
    m_itemImage->SetBrushFromTexture(itemInfo.icon);
    m_lineStr = lineStr;
    m_itemInfo = itemInfo;
    this->SetText(FString::FromInt(m_itemInfo.count));
}

void UItemWidget::GetItemWidgetInfo(FString& outLineStr, FItemTableRow& outItemInfo)
{
    outLineStr = m_lineStr;
    outItemInfo = m_itemInfo;
}

FItemTableRow& UItemWidget::GetItemInfo()
{
    return m_itemInfo;
}

void UItemWidget::SetClickedFlag(const bool flag)
{
    if (m_isClicked == flag) {
        return;
    }
    m_isClicked = flag;
    if (m_isClicked) {
        FButtonStyle style = m_itemBtn->GetStyle();
        style.Normal.TintColor = FSlateColor(FLinearColor::Red);
        m_itemBtn->SetStyle(style);
        // 获取父控件GridPanel,用以遍历清除其它选中项,保证单一选中
        TObjectPtr<UWidget> widget = this->GetParent();
        while (widget != nullptr) {
            if (widget->IsA<UUniformGridPanel>()) {
                // 遍历获取itemWidget
                TObjectPtr<UUniformGridPanel> gridPanel = Cast<UUniformGridPanel>(widget);
                for (auto child : gridPanel->GetAllChildren()) {
                    TObjectPtr<UItemWidget> item = Cast<UItemWidget>(child);
                    // 找到非当前项的其它被选项之后，将其选中状态取消
                    if (item->GetClickedFlag() && item != this) {
                        item->SetClickedFlag(false);
                    }
                }
            }
            widget = widget->GetParent();
        }
    } else {
        FButtonStyle style = m_itemBtn->GetStyle();
        style.Normal.TintColor = FSlateColor(FLinearColor::White);
        m_itemBtn->SetStyle(style);
    }
}

bool UItemWidget::GetClickedFlag()
{
    return m_isClicked;
}

void UItemWidget::ClearWidgetInfo()
{
    FItemTableRow emptyInfo;
    m_itemInfo = emptyInfo;
    m_itemImage->SetBrushFromTexture(nullptr);
    m_lineStr.Empty();
    this->SetText("0");
}

FString& UItemWidget::GetLineStr()
{
    return m_lineStr;
}

void UItemWidget::ChangeItemCount(const int32 numb)
{
    m_itemInfo.count = m_itemInfo.count + numb;
    if (m_itemInfo.count > 0) {
        this->SetText(FString::FromInt(m_itemInfo.count));
        return;
    } else {
        this->ClearWidgetInfo();
    }
}

void UItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    m_isClicked = false;

    m_itemBtn->OnClicked.AddDynamic(this, &UItemWidget::OnBtnClicked);
}

void UItemWidget::OnBtnClicked()
{
    this->SetClickedFlag(!m_isClicked);
}
