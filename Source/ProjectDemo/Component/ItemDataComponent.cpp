// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataComponent.h"
#include "../Public/MyGameInstance.h"

// Sets default values for this component's properties
UItemDataComponent::UItemDataComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UItemDataComponent::BeginPlay()
{
    Super::BeginPlay();

    // 初始化物品数据
    if (m_initItem.Num() <= 0) {
        return;
    }
    TObjectPtr<UMyGameInstance> gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
    for (auto item : m_initItem) {
        FItemTableRow itemStruct = *gameInstance->GetItemStruct(item.Key);
        itemStruct.count = item.Value;
        m_itemMap.Add({ item.Key, itemStruct });
        UE_LOG(LogTemp, Warning, TEXT("UItemDataComponent::BeginPlay() : %s"), *itemStruct.name);
    }
}

// Called every frame
void UItemDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

TMap<FString, FItemTableRow> UItemDataComponent::TakeItemMap()
{
    auto resMap = m_itemMap;
    m_itemMap.Empty();
    return resMap;
}

TMap<FString, FItemTableRow>& UItemDataComponent::GetItemMap()
{
    return m_itemMap;
}

void UItemDataComponent::AddItem(const FString& itemStr, const FItemTableRow& itemData)
{
    if (m_itemMap.Contains(itemStr)) {
        m_itemMap[itemStr].count += itemData.count;
    } else {
        m_itemMap.Add(itemStr, itemData);
    }
    UE_LOG(LogTemp, Warning, TEXT("UItemDataComponent::AddItem 2 %s : %d"), *itemStr, m_itemMap[itemStr].count);
}

void UItemDataComponent::RemoveItem(const FString& itemStr, const FItemTableRow& itemData)
{
    if (m_itemMap.Contains(itemStr)) {
        m_itemMap[itemStr].count -= itemData.count;
        if (m_itemMap[itemStr].count <= 0) {
            m_itemMap.Remove(itemStr);
        }
    }
}

void UItemDataComponent::RemoveItem(const FString& itemStr, const int numb)
{
    if (m_itemMap.Contains(itemStr)) {
        m_itemMap[itemStr].count -= numb;
        if (m_itemMap[itemStr].count <= 0) {
            m_itemMap.Remove(itemStr);
        }
    }
}

void UItemDataComponent::ClearAllItem()
{
    m_itemMap.Empty();
}

