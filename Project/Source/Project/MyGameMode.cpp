// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "MyOject.h"

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	UMyOject* MyObj = NewObject<UMyOject>();
	if (MyObj != nullptr)
	{
		MyObj->PrintHello();
	}
}
