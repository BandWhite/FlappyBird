// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LandActor.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

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
private:
	UPROPERTY()
	class ABgActor* BgActor;

	UPROPERTY()
	class ALandActor* LandActor;

	UPROPERTY()
	class APipelineActor* PipelineActor;
};
