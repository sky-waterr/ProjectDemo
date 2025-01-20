// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Struct/Weapon.h"
#include "ItemDataComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTDEMO_API UItemDataComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UItemDataComponent();

    UFUNCTION(BlueprintCallable, Category = "Item")
    TMap<FString, FItemTableRow> TakeItemMap();
    UFUNCTION(BlueprintCallable, Category = "Item")
    TMap<FString, FItemTableRow>& GetItemMap();
    UFUNCTION(BlueprintCallable, Category = "Item")
    void AddItem(const FString& itemStr, const FItemTableRow& itemData);
    void RemoveItem(const FString& itemStr, const FItemTableRow& itemData);
    void RemoveItem(const FString& itemStr, const int numb);
    UFUNCTION(BlueprintCallable, Category = "Item")
    void ClearAllItem();
protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData", meta = (AllowPrivateAccess = "true"))
    TMap<FString, int> m_initItem;
    TMap<FString, FItemTableRow> m_itemMap;  // �洢�����������ݿ�����
};
