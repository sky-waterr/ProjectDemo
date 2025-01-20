// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
    UDataTable* dataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/BluePrint/BpItemTable.BpItemTable'")));

    if (dataTable != nullptr) {
        TArray<FName> rowNames = dataTable->GetRowNames();

        for (auto row : rowNames) {
            m_itemTableMap.Add(row.ToString(), dataTable->FindRow<FItemTableRow>(row, TEXT("BpWeaponRows")));
            UE_LOG(LogTemp, Log, TEXT("Row Name: %s, Name: %s"),*row.ToString(), *m_itemTableMap[row.ToString()]->name);
        }
    }
}

FItemTableRow* UMyGameInstance::GetItemStruct(const FString& lineIndex)
{
    return m_itemTableMap[lineIndex];
}
