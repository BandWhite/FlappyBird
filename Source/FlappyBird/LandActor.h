// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandActor.generated.h"

UCLASS()
class FLAPPYBIRD_API ALandActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALandActor();
	void SetSpeed(float Speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateLandLocation(float DeltaTime);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* LandSpriteRender;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* LandSpriteRenderNext;

	UPROPERTY(EditAnywhere)
	float Speed;
};
