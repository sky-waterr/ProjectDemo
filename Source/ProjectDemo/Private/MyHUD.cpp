// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Component/ItemDataComponent.h"
#include "../Component/DialogueComponent.h"
#include "MyGameInstance.h"
#include "MyPlayerController.h"
#include "../HUD/MainWidget.h"

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    m_npcType = NpcType::OTHER;

    // 获取mainWidget实例
    TObjectPtr<AMyPlayerController> controller = Cast<AMyPlayerController>(GetOwningPlayerController());
    if (m_mainWidgetClass != nullptr) {
        m_mainWidget = CreateWidget<UMainWidget>(controller, m_mainWidgetClass);
        ShowInteractBtn(false);
        ShowInteractTalk(false);
    }

    // 获取shopWidget实例
    TSubclassOf<UUserWidget> shopClass = LoadClass<UUserWidget>(this, TEXT("/Game/BluePrint/HUD/BpShopWidget.BpShopWidget_C"));
    if (shopClass != nullptr) {
        m_shopWidget = CreateWidget<UUserWidget>(controller, shopClass);
        if (m_shopWidget != nullptr) {
            TObjectPtr<UItemUniformGridPanel> itemBox = Cast<UItemUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("itemBox")));
            TObjectPtr<UItemUniformGridPanel> shopBox = Cast<UItemUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("shopBox")));
            int itemNumb = controller->GetCurPlayerItemMax();
            itemBox->InitItemGridPanel(m_shopWidget, itemNumb);
            shopBox->InitItemGridPanel(m_shopWidget, 24);     // 24为设定的商店物品数量
        }
    }

    // 获取itemWidget实例
    TSubclassOf<UUserWidget> propertyClass = LoadClass<UUserWidget>(this, TEXT("/Game/BluePrint/HUD/BpPropertyWidget.BpPropertyWidget_C"));
    if (propertyClass != nullptr) {
        m_propertyWidget = CreateWidget<UUserWidget>(controller, propertyClass);
        if (m_propertyWidget != nullptr) {
            TObjectPtr<UItemUniformGridPanel> itemBox = Cast<UItemUniformGridPanel>(m_propertyWidget->GetWidgetFromName(TEXT("itemBox")));
            int itemNumb = controller->GetCurPlayerItemMax();
            itemBox->InitItemGridPanel(m_propertyWidget, itemNumb);
        }
    }
    this->InitCompFunc();

    this->ShowMainWidget();
}

void AMyHUD::InitCompFunc()
{
    // mainwidget的交互按钮
    TObjectPtr<UButton> talkBtn = Cast<UButton>(m_mainWidget->GetWidgetFromName(TEXT("m_interactBtn")));
    if (talkBtn != nullptr) {
        talkBtn->OnClicked.AddDynamic(this, &AMyHUD::OnTalkBtnClicked);
    }

    // shopWidget的交互按钮
    TObjectPtr<UButton> closeBtn = Cast<UButton>(m_shopWidget->GetWidgetFromName(TEXT("closeBtn")));
    if (closeBtn != nullptr) {
        closeBtn->OnClicked.AddDynamic(this, &AMyHUD::OnCloseBtnClicked);
    }
    TObjectPtr<UButton> buyBtn = Cast<UButton>(m_shopWidget->GetWidgetFromName(TEXT("buyBtn")));
    if (buyBtn != nullptr) {
        buyBtn->OnClicked.AddDynamic(this, &AMyHUD::OnBuyBtnClicked);
    }
}

void AMyHUD::SetItemBox(TObjectPtr<UItemUniformGridPanel> itemBox, TSubclassOf<UItemWidget> itemClass, TObjectPtr<AMyPlayerController> controller)
{
    // 获取当前玩家身上的物品
    TObjectPtr<APawn> player = controller->GetPawn();
    // 获取当前角色的数据组件
    if (player != nullptr) {
        TObjectPtr<UItemDataComponent> itemComponent = player->FindComponentByClass<UItemDataComponent>();
        if (itemComponent != nullptr) {
            TMap<FString, FItemTableRow> itemData = itemComponent->GetItemMap();
            for (auto data : itemData) {
                itemBox->AddItem(data.Key, data.Value);
            }
        }
    }
}

void AMyHUD::ShowMainWidget()
{
    m_mainWidget->AddToViewport();
    m_propertyWidget->RemoveFromParent();
    m_shopWidget->RemoveFromParent();
}

void AMyHUD::ShowShopWidget()
{
    if (m_shopWidget->IsInViewport()) {
        this->ShowMainWidget();
        return;
    }
    TObjectPtr<AMyPlayerController> controller = Cast<AMyPlayerController>(GetOwningPlayerController());
    if (m_shopWidget != nullptr) {
        TObjectPtr<UItemUniformGridPanel> itemBox = Cast<UItemUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("itemBox")));
        TObjectPtr<UItemUniformGridPanel> shopBox = Cast<UItemUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("shopBox")));
        shopBox->ReInitItemGridPanel();
        shopBox->ReinitByItems(controller->GetTouchedNpcItems());
        itemBox->ReInitItemGridPanel();
        itemBox->ReinitByItems(controller->GetPlayerBackageItems());
        // 显示商店界面
        m_shopWidget->AddToViewport();
        m_mainWidget->RemoveFromParent();
        m_propertyWidget->RemoveFromParent();
    }
}

void AMyHUD::ChangeItemBoxState(const TObjectPtr<AMyPlayerController> controller)
{
    TObjectPtr<APawn> player = controller->GetPawn();
    TArray<AActor*> otherActors = controller->GetTouchedNpcs();
    // 遍历重叠的目标
    for (AActor* actor : otherActors) {
        if (actor == player) {
            continue;
        }
        TObjectPtr<UFunction> func = actor->FindFunction(TEXT("ChangePaperFlipbook"));
        if (func != nullptr) {
            actor->ProcessEvent(func, nullptr);
        }
    }
}

void AMyHUD::ShowInteractBtn(const bool& flag)
{
    UE_LOG(LogTemp, Warning, TEXT("This is ShowInteractBtn.%d"), flag);
    if (m_mainWidget == nullptr) {
        return;
    }
    if (flag) {
        m_mainWidget->ShowInteractBtn(ESlateVisibility::Visible);
    } else {
        m_mainWidget->ShowInteractBtn(ESlateVisibility::Hidden);
    }
}

void AMyHUD::OnTalkBtnClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("AMyHUD::OnTalkBtnClicked()"));
    // 获取当前NPC的对话标签号
    if (m_mainWidget == nullptr) {
        return;
    }
    if (m_mainWidget->GetInteractBtnState() != ESlateVisibility::Visible) {
        return;
    }

    TObjectPtr<AMyPlayerController> controller = Cast<AMyPlayerController>(GetOwningPlayerController());

    if (m_lineArray.Num() == 0 && m_curLineIndex == 0 && m_itemMap.Num() == 0) {
        controller->GetTouchedNpcAllData(m_itemMap, m_lineArray, m_npcType);
        UE_LOG(LogTemp, Warning, TEXT("AMyHUD::OnTalkBtnClicked() npctype %d"), m_npcType);
    }

    if (m_lineArray.Num() > 0 && m_curLineIndex < m_lineArray.Num()) {
        if (m_curLineIndex == 0) {
            // 更换操作模式到对话状态
            controller->ClearInputBinds();
            controller->SetDialogueBind();
            m_mainWidget->ShowInteractTalk(ESlateVisibility::Visible);
        }
        m_mainWidget->SetInteractText(m_lineArray[m_curLineIndex]);
        m_curLineIndex++;
        return;
    } else {
        m_mainWidget->ShowInteractTalk(ESlateVisibility::Hidden);
        if (m_npcType == NpcType::SHOP) {
            UE_LOG(LogTemp, Warning, TEXT("AMyHUD::OnTalkBtnClicked() is shop"));
            this->ShowShopWidget();
        }
        // 更换操作模式到默认状态
        controller->ClearInputBinds();
        controller->SetDefaultBind();
    }

    if (m_npcType != NpcType::SHOP && m_itemMap.Num() > 0) {
        if (m_npcType == NpcType::ITEMBOX) {
            this->ChangeItemBoxState(controller);
        }
        for (auto data : m_itemMap) {
            controller->PlayerGetItem(data.Key, data.Value.count);
            FString info = "Get " + data.Key + "x" + FString::FromInt(data.Value.count);
            m_mainWidget->AddPopupInfo(info);
        }
        m_itemMap.Empty();
    }
}

void AMyHUD::ShowInteractTalk(const bool& flag)
{
    if (m_mainWidget == nullptr) {
        return;
    }
    if (flag) {
        m_mainWidget->ShowInteractTalk(ESlateVisibility::Visible);
    } else {
        m_mainWidget->ShowInteractTalk(ESlateVisibility::Hidden);
    }
}

void AMyHUD::AddPopupInfo(const FString& info)
{
    if (m_mainWidget == nullptr) {
        return;
    }
    m_mainWidget->AddPopupInfo(info);
}

void AMyHUD::SlotOnPressTalkBtn()
{
    if (m_mainWidget == nullptr) {
        return;
    }
    UButton* talkBtn = Cast<UButton>(m_mainWidget->GetWidgetFromName(TEXT("m_interactBtn")));
    if (talkBtn != nullptr) {
        talkBtn->OnClicked.Broadcast();
    }
}

void AMyHUD::SlotOnPropertyBtn()
{
    if (m_propertyWidget->IsInViewport()) {
        this->ShowMainWidget();
        return;
    }
    TObjectPtr<AMyPlayerController> controller = Cast<AMyPlayerController>(GetOwningPlayerController());
    if (m_propertyWidget != nullptr) {
        TObjectPtr<UItemUniformGridPanel> itemBox = Cast<UItemUniformGridPanel>(m_propertyWidget->GetWidgetFromName(TEXT("itemBox")));
        TSubclassOf<UItemWidget> itemClass = LoadClass<UItemWidget>(this, TEXT("/Game/BluePrint/HUD/BpItemWidget.BpItemWidget_C"));
        this->SetItemBox(itemBox, itemClass, controller);
        // 显示属性界面
        m_propertyWidget->AddToViewport();
        m_mainWidget->RemoveFromParent();
        m_shopWidget->RemoveFromParent();
    }
}

void AMyHUD::SlotOnShopBtn()
{
    this->ShowShopWidget();
}

void AMyHUD::OnBuyBtnClicked()
{
    if (m_shopWidget != nullptr) {
        TObjectPtr<UUniformGridPanel> shopBox = Cast<UUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("shopBox")));
        TObjectPtr<UItemUniformGridPanel> itemBox = Cast<UItemUniformGridPanel>(m_shopWidget->GetWidgetFromName(TEXT("itemBox")));
        TObjectPtr<AMyPlayerController> controller = Cast<AMyPlayerController>(GetOwningPlayerController());
        for (auto child : shopBox->GetAllChildren()) {
            TObjectPtr<UItemWidget> item = Cast<UItemWidget>(child);
            // 找到当前选中的子项
            if (item != nullptr && item->GetClickedFlag()) {
                FItemTableRow itemInfo;
                FString lineStr;
                item->GetItemWidgetInfo(lineStr, itemInfo);
                controller->PlayerGetItem(lineStr, itemInfo.count);
                itemBox->AddItem(lineStr, itemInfo);
            }
        }
    }
}

void AMyHUD::OnCloseBtnClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("AMyHUD::OnCloseBtnClicked()"));
    this->ShowMainWidget();
}

void AMyHUD::OnNpcInteractEnd()
{
    UE_LOG(LogTemp, Warning, TEXT("AMyHUD::OnNpcInteractEnd()"));
    m_lineArray.Empty();
    m_curLineIndex = 0;
    m_itemMap.Empty();
    m_npcType = NpcType::OTHER;
}
