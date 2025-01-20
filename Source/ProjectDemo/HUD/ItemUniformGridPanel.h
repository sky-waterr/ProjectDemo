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
    // ��ȡ-����itemWidget�еĵ�һ���յ�����
    UWidget* GetFirstEmptyChild();
    // ��ȡ-����itemWidget�еĵ�һ���յ������ǩ
    int GetFirstEmptyIndex();
    // ����-��ȡ��ǰ��ѡ�е�����
    void SetSelectedIndex(const int index);
    // ��ȡ-��ǰ��ѡ�е�����
    int GetSelectedIndex();
    // ���-����itemWidget���������(��ʼ��)
    void ClearAllItemWidget();
    // ���-���ߣ���ͬ�����������Ϊ����������
    void AddItem(const FString& lineStr, const FItemTableRow& itemInfo);
    // ���-������ߣ�ʹ��ǰ�뱣֤itemBox��ʼ��/������ɣ���ͬ�����������Ϊ����������
    void ReinitByItems(const TMap<FString, FItemTableRow>& items);
    // ����-ָ����������
    void ReduceItem(const FString& lineStr, const int count);
    // ����-��ǰGridPanel�е������Ѵ�������Ϊ��ʼ��
    void ReInitItemGridPanel();
    // ��ʼ��-Ϊ��ǰItemGridPanel��ʼ��ָ�������ĸ���
    void InitItemGridPanel(const TObjectPtr<UUserWidget> widget, const int numb);
private:
    int m_selectIndex;
};
