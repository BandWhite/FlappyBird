// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API ABirdGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	void AddScore();
	void ResetScore();
	int32 GetScore();
	
private:
	int32 Score;
	
};
