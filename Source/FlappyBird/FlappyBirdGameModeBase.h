// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LandActor.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

enum class EGameState:uint8
{
	EGS_Menu,
	EGS_Gaming,
	EGS_Over,
};

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFlappyBirdGameModeBase();
	virtual void BeginPlay() override;

	void ChangeState(EGameState State);

	UFUNCTION(Exec)
	void CMD(int32 cmd);

private:
	UPROPERTY()
	class ABgActor* BgActor;

	UPROPERTY()
	class ALandActor* LandActor;

	UPROPERTY()
	class APipelineActor* PipelineActor;

	UPROPERTY()
	class ABirdPawn* BirdPawn;

	EGameState CurrentState;

	float GameSpeed;
};
