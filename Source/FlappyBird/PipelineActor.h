// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipelineActor.generated.h"

UCLASS()
class FLAPPYBIRD_API APipelineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipelineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RestPieGroups();

	void RandomPipeGroupZ(class USceneComponent* PipeGroup);

	void UpdatePipeGroupPosition(float DeltaTime);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<USceneComponent*> PipeGroups;

private:
	float Speed; //速度
	bool bRun; //管道滚动
	float GroupInterval;//管道间隔
};
