// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonManager.h"
#include "Runtime/Json/Public/Json.h"

JsonManager::JsonManager()
{
	Directory = FPaths::GameDir();
}

JsonManager::JsonManager(FString filename)
	:FileName(filename)
{
	Directory = FPaths::GameDir();
	FString path = Directory + FileName;
	if (!FPaths::FileExists(path))
		FFileHelper::SaveStringToFile("",*path);
}


JsonManager::~JsonManager()
{

}

void JsonManager::SavaData(FString str)
{
	FString path = Directory + FileName;
	UE_LOG(LogTemp, Warning, TEXT("Save in %s"), *path);
	FFileHelper::SaveStringToFile(*str, *path);
}


TSharedPtr<FJsonObject> JsonManager::LoadData()
{
	FString jsonstr;
	FString path = Directory + FileName;
	FFileHelper::LoadFileToString(jsonstr, *path);
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<>::Create(jsonstr);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject);
	
	FJsonSerializer::Deserialize(reader, jsonObj);
	return jsonObj;
}


