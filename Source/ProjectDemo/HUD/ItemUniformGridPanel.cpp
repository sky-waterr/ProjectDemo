// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "../Public/MyPlayerController.h"

UWidget* UItemUniformGridPanel::GetFirstEmptyChild()
{
    // �������е�itemWidget���࣬���ҵ�һ���յ�����
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
    // �������е�itemWidget���࣬���ҵ�һ���յ�����
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
    // �������е�itemWidget���࣬������û����ͬ������
    int emptyIndex = -1;
    for (int i = 0; i < this->GetChildrenCount(); ++i) {
        TObjectPtr<UItemWidget> itemWidget = Cast<UItemWidget>(this->GetChildAt(i));
        if (itemWidget != nullptr) {
            if (itemWidget->GetLineStr().IsEmpty()) {
                emptyIndex = (emptyIndex == -1) ? i : emptyIndex;  // �ж��Ƿ��ǵ�һ��������ֵ
            } else if (itemWidget->GetLineStr() == lineStr) {
                itemWidget->ChangeItemCount(itemInfo.count);    // �ҵ�ͬ�������ݣ���ı���������
                return;
            }
        }
    }
    // û�ҵ���ͬ���ݣ��ڵ�һ�������ݴ��������
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
            this->AddChildToUniformGrid(item, i / 4, i % 4);    // ÿ���Ų�4��
            TObjectPtr<UUniformGridSlot> itemSlot = Cast<UUniformGridSlot>(item->Slot);
            if (itemSlot != nullptr) {
                itemSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center); // ˮƽ����
                itemSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top); // ��ֱ���뵽����
            }
        }
    }
}
