// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "../Public/MyPlayerController.h"

UWidget* UItemUniformGridPanel::GetFirstEmptyChild()
{
    // 遍历所有的itemWidget子类，查找第一个空的子类
    for (auto child : this->GetAllChildren()) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(child);
        if (itemWidget != nullptr && itemWidget->GetItemInfo().name.IsEmpty()) {
            return child;
        }
    }
    return nullptr;
}

int UItemUniformGridPanel::GetFirstEmptyIndex()
{
    // 遍历所有的itemWidget子类，查找第一个空的子类
    for (int i = 0; i < this->GetChildrenCount(); ++i) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(this->GetChildAt(i));
        if (itemWidget != nullptr && itemWidget->GetItemInfo().name.IsEmpty()) {
            return i;
        }
    }
    return -1;
}

void UItemUniformGridPanel::SetSelectedIndex(const int index)
{
    m_selectIndex = index;
}

int UItemUniformGridPanel::GetSelectedIndex()
{
    return m_selectIndex;
}

void UItemUniformGridPanel::ClearAllItemWidget()
{
    for (auto child : this->GetAllChildren()) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(child);
        if (itemWidget != nullptr) {
            itemWidget->ClearWidgetInfo();
        }
    }
}

void UItemUniformGridPanel::AddItem(const FString& lineStr, const FItemTableRow& itemInfo)
{
    // 遍历所有的itemWidget子类，查找有没有相同的数据
    int emptyIndex = -1;
    for (int i = 0; i < this->GetChildrenCount(); ++i) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(this->GetChildAt(i));
        if (itemWidget != nullptr) {
            if (itemWidget->GetLineStr().IsEmpty()) {
                emptyIndex = (emptyIndex == -1) ? i : emptyIndex;  // 判断是否是第一次遇到空值
            } else if (itemWidget->GetLineStr() == lineStr) {
                itemWidget->ChangeItemCount(itemInfo.count);    // 找到同样的数据，则改变数据数量
                return;
            }
        }
    }
    // 没找到相同数据，在第一个空数据处添加子项
    Cast<UItemWidget>(this->GetChildAt(emptyIndex))->SetItemWidgetInfo(lineStr, itemInfo);
}

void UItemUniformGridPanel::ReinitByItems(const TMap<FString, FItemTableRow>& items)
{
    if (items.Num() > this->GetChildrenCount()) {
        UE_LOG(LogTemp, Error, TEXT("UItemUniformGridPanel::ReinitByItems : item count > itemBox maxsize"));
        return;
    }
    int index = 0;
    for (auto item : items) {
        Cast<UItemWidget>(this->GetChildAt(index))->SetItemWidgetInfo(item.Key, item.Value);
        ++index;
    }
}

void UItemUniformGridPanel::ReduceItem(const FString& lineStr, const int count)
{
    for (int i = 0; i < this->GetChildrenCount(); ++i) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(this->GetChildAt(i));
        if (itemWidget != nullptr) {
            if (itemWidget->GetLineStr().IsEmpty() && itemWidget->GetLineStr() == lineStr) {
                itemWidget->ChangeItemCount(-count);
                return;
            }
        }
    }
}

void UItemUniformGridPanel::ReInitItemGridPanel()
{
    for (auto child : this->GetAllChildren()) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(child);
        if (itemWidget != nullptr && !itemWidget->GetItemInfo().name.IsEmpty()) {
            itemWidget->ClearWidgetInfo();
        }
    }
}

void UItemUniformGridPanel::InitItemGridPanel(const TObjectPtr<UUserWidget> widget, const int numb)
{
    TSubclassOf<UItemWidget> itemClass = LoadClass<UItemWidget>(widget, TEXT("/Game/BluePrint/HUD/BpItemWidget.BpItemWidget_C"));
    if (itemClass != nullptr) {
        for (int i = 0; i < numb; i++) {
            TObjectPtr<UItemWidget> item = CreateWidget<UItemWidget>(widget, itemClass);
            this->AddChildToUniformGrid(item, i / 4, i % 4);    // 每行排布4个
            TObjectPtr<UUniformGridSlot> itemSlot = Cast<UUniformGridSlot>(item->Slot);
            if (itemSlot != nullptr) {
                itemSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center); // 水平居中
                itemSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top); // 垂直对齐到顶部
            }
        }
    }
}
