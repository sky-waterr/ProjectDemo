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

    // ��������ᱻ�������� TextBlock �����ֲ�������ʾ״̬�仯
    UFUNCTION(BlueprintCallable)
    void SetText(const FString& str);
    void SetImage(const TObjectPtr<UTexture2D> icon);
    // ����-��ǰitemWidget����Ʒ�кź���Ʒ��Ϣ
    void SetItemWidgetInfo(const FString& lineStr, const FItemTableRow& itemInfo);
    // ��ȡ-��ǰitemWidget����Ʒ�кź���Ʒ��Ϣ
    void GetItemWidgetInfo(FString& outLineStr, FItemTableRow& outItemInfo);
    // ��ȡ-��ǰitemWidget����Ʒ��Ϣ
    FItemTableRow& GetItemInfo();
    // ����-��ǰ��ѡ��״̬
    void SetClickedFlag(const bool flag);
    // ��ȡ-��ǰ��ѡ��״̬
    bool GetClickedFlag();
    // ���-��ǰwidget��������
    void ClearWidgetInfo();
    // ��ȡ-��ǰ��Ʒ��Ӧ���к�
    FString& GetLineStr();
    // ����-��ǰ��Ʒ������,����������<=0,���itemWidget�����������
    void ChangeItemCount(const int32 numb);

protected:
    virtual void NativeConstruct() override;

    // ���صİ�ť��������
    UFUNCTION(BlueprintCallable, Category = "ItemWidget")
    void OnBtnClicked();

protected:
    // button�Ŀؼ�
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> m_itemBtn;

    // TextBlock �ؼ�����
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
