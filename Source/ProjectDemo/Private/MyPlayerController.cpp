// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "StructUtils/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "../Struct/Weapon.h"
#include "../Component/ItemDataComponent.h"
#include "../Component/DialogueComponent.h"
#include "MyGameInstance.h"
#include "Components/SphereComponent.h"

AMyPlayerController::AMyPlayerController()
    : m_hud(nullptr)
    , playerInputMapping(nullptr)
    , myMoveAction(nullptr)
    , myInteraction(nullptr)
    , m_dircX(0)
    , m_dircY(0)
    , m_playerItemNumb(24)
{
}

void AMyPlayerController::BeginPlay()
{
    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if (LocalPlayer) {
        UEnhancedInputLocalPlayerSubsystem* inputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (inputSubsystem != nullptr && playerInputMapping != nullptr) {
            inputSubsystem->AddMappingContext(playerInputMapping, 0);
        }
    }
    this->SetDefaultBind();

    m_hud = Cast<AMyHUD>(GetHUD());
}

void AMyPlayerController::OnMove(const FInputActionValue& value)
{
    FVector2D MoveValue = value.Get<FVector2D>();
    const FRotator Ro = this->GetControlRotation();
    const FRotator YawRo(0, Ro.Yaw, 0);
    const FVector PlayerF = FRotationMatrix(YawRo).GetUnitAxis(EAxis::X);
    const FVector PlayerR = FRotationMatrix(YawRo).GetUnitAxis(EAxis::Y);

    GetPawn()->AddMovementInput(PlayerF, MoveValue.X);
    GetPawn()->AddMovementInput(PlayerR, MoveValue.Y);
    m_dircX = MoveValue.X;
    m_dircY = MoveValue.Y;
}

void AMyPlayerController::SetDefaultBind()
{
    UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (inputComponent != nullptr) {
        inputComponent->BindAction(myMoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMove);
        inputComponent->BindAction(myInteraction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInterBtnPress);
        inputComponent->BindAction(m_propertyAct, ETriggerEvent::Triggered, this, &AMyPlayerController::OnPropertyBtnClicked);
    }
}

void AMyPlayerController::SetDialogueBind()
{
    UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (inputComponent != nullptr) {
        inputComponent->BindAction(myInteraction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInterBtnPress);
    }
}

void AMyPlayerController::ClearInputBinds()
{
    UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (inputComponent != nullptr) {
        inputComponent->ClearActionBindings();
    }
}

int AMyPlayerController::GetCurPlayerItemMax()
{
    return m_playerItemNumb;
}

void AMyPlayerController::SetCurPlayerItemMax(const int numb)
{
    m_playerItemNumb = numb;
}

void AMyPlayerController::PlayerGetItem(const FString& itemStr, const int numb)
{
    TObjectPtr<APawn> player = GetPawn();
    if (player) {
        TObjectPtr<UMyGameInstance> gameInstance = Cast<UMyGameInstance>(GetGameInstance());
        TObjectPtr<UItemDataComponent> itemComp = player->FindComponentByClass<UItemDataComponent>();
        if (itemComp != nullptr) {
            auto itemData = *gameInstance->GetItemStruct(itemStr);
            itemData.count = numb;
            itemComp->AddItem(itemStr, itemData);
        }
    }
}

void AMyPlayerController::PlayerLostItem(const FString& itemStr, const int numb)
{
    TObjectPtr<APawn> player = GetPawn();
    if (player) {
        TObjectPtr<UItemDataComponent> itemComp = player->FindComponentByClass<UItemDataComponent>();
        if (itemComp != nullptr) {
            itemComp->RemoveItem(itemStr, numb);
        }
    }
}

TMap<FString, FItemTableRow> AMyPlayerController::GetPlayerBackageItems()
{
    // 获取当前玩家身上的物品
    TObjectPtr<APawn> player = this->GetPawn();
    TMap<FString, FItemTableRow> itemDatas;
    // 获取当前角色的数据组件
    if (player != nullptr) {
        TObjectPtr<UItemDataComponent> itemComponent = player->FindComponentByClass<UItemDataComponent>();
        if (itemComponent != nullptr) {
            itemDatas = itemComponent->GetItemMap();
        }
    }
    return itemDatas;
}

void AMyPlayerController::GetTouchedNpcAllData(TMap<FString, FItemTableRow>& outItems, TArray<FString>& outDialogues, NpcType& outNpcType)
{
    // 获取当前商店NPC身上的物品
    TObjectPtr<APawn> player = this->GetPawn();
    TObjectPtr<UItemDataComponent> itemComponent;
    TObjectPtr<UDialogueComponent> dialogueComponent;

    // 获取当前重叠的组NPC
    if (player != nullptr) {
        TObjectPtr<USphereComponent> sphere = player->FindComponentByClass<USphereComponent>();
        if (sphere != nullptr) {
            TArray<AActor*> otherActors;
            sphere->GetOverlappingActors(otherActors);
            // 遍历重叠的目标
            for (AActor* actor : otherActors) {
                if (actor != player) {
                    itemComponent = actor->FindComponentByClass<UItemDataComponent>();
                    dialogueComponent = actor->FindComponentByClass<UDialogueComponent>();
                    break;
                }
            }
        }
    }
    if (dialogueComponent != nullptr) {
        outDialogues = dialogueComponent->GetNpcLineArray();
        outNpcType = dialogueComponent->GetNpcType();
        UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::GetTouchedNpcAllData %d"), outNpcType);
    }
    if (itemComponent != nullptr) {
        if (outNpcType == NpcType::SHOP) {
            outItems = itemComponent->GetItemMap();
        } else {
            outItems = itemComponent->TakeItemMap();
        }
    }
}

TArray<AActor*> AMyPlayerController::GetTouchedNpcs()
{
    TObjectPtr<APawn> player = this->GetPawn();
    TArray<AActor*> otherActors;

    // 获取当前重叠的组NPC
    if (player != nullptr) {
        TObjectPtr<USphereComponent> sphere = player->FindComponentByClass<USphereComponent>();
        if (sphere != nullptr) {
            sphere->GetOverlappingActors(otherActors);
        }
    }
    return otherActors;
}

TMap<FString, FItemTableRow> AMyPlayerController::GetTouchedNpcItems()
{
    // 获取当前商店NPC身上的物品
    TObjectPtr<APawn> player = this->GetPawn();
    TObjectPtr<UItemDataComponent> itemComponent;
    TMap<FString, FItemTableRow> itemDatas;

    // 获取当前重叠的组NPC
    if (player != nullptr) {
        TObjectPtr<USphereComponent> sphere = player->FindComponentByClass<USphereComponent>();
        if (sphere != nullptr) {
            TArray<AActor*> otherActors;
            sphere->GetOverlappingActors(otherActors);
            // 遍历重叠的目标
            for (AActor* actor : otherActors) {
                if (actor != player) {
                    itemComponent = actor->FindComponentByClass<UItemDataComponent>();
                    break;
                }
            }
        }
    }
    if (itemComponent != nullptr) {
        itemDatas = itemComponent->GetItemMap();
    }
    return itemDatas;
}

void AMyPlayerController::GetTouchedNpcDialogueData(TArray<FString>& outLineData, NpcType outNpcFlag)
{
    TObjectPtr<APawn> player = this->GetPawn();
    TObjectPtr<UDialogueComponent> dialogueComponent;

    // 获取当前重叠的组NPC
    if (player != nullptr) {
        TObjectPtr<USphereComponent> sphere = player->FindComponentByClass<USphereComponent>();
        if (sphere != nullptr) {
            TArray<AActor*> otherActors;
            sphere->GetOverlappingActors(otherActors);
            // 遍历重叠的目标
            for (AActor* actor : otherActors) {
                if (actor != player) {
                    dialogueComponent = actor->FindComponentByClass<UDialogueComponent>();
                    break;
                }
            }
        }
    }
    if (dialogueComponent != nullptr) {
        outLineData = dialogueComponent->GetNpcLineArray();
        outNpcFlag = dialogueComponent->GetNpcType();
    }
}

void AMyPlayerController::OnInterBtnPress(const FInputActionValue& value)
{
    if (m_hud != nullptr) {
        m_hud->SlotOnPressTalkBtn();
    }
}

void AMyPlayerController::OnPropertyBtnClicked(const FInputActionValue& value)
{
    if (m_hud != nullptr) {
        m_hud->SlotOnPropertyBtn();
    }
}
