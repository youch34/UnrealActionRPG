// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYGAME_API JsonManager
{
public:
	JsonManager();
	JsonManager(FString filename);
	~JsonManager();

public:
	void SetFileName(FString name) { this->FileName = name; }
	void SavaData(FString str);

	TSharedPtr<class FJsonObject> LoadData();
private:
	FString FileName;
	FString Directory;
};

