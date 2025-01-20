// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "ItemWidget.h"
#include "ItemUniformGridPanel.generated.h"

/**
 *
 */
UCLASS()
class PROJECTDEMO_API UItemUniformGridPanel : public UUniformGridPanel
{
    GENERATED_BODY()

public:
    // 获取-子类itemWidget中的第一个空的子类
    UWidget* GetFirstEmptyChild();
    // 获取-子类itemWidget中的第一个空的子类标签
    int GetFirstEmptyIndex();
    // 设置-获取当前被选中的子项
    void SetSelectedIndex(const int index);
    // 获取-当前被选中的子项
    int GetSelectedIndex();
    // 清空-所有itemWidget子类的数据(初始化)
    void ClearAllItemWidget();
    // 添加-道具（相同的数据则表现为数量上升）
    void AddItem(const FString& lineStr, const FItemTableRow& itemInfo);
    // 添加-多个道具（使用前请保证itemBox初始化/重置完成，相同的数据则表现为数量上升）
    void ReinitByItems(const TMap<FString, FItemTableRow>& items);
    // 减少-指定道具数量
    void ReduceItem(const FString& lineStr, const int count);
    // 重置-当前GridPanel中的所有已存在数据为初始化
    void ReInitItemGridPanel();
    // 初始化-为当前ItemGridPanel初始化指定数量的格子
    void InitItemGridPanel(const TObjectPtr<UUserWidget> widget, const int numb);
private:
    int m_selectIndex;
};
