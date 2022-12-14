// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BgActor.generated.h"

UCLASS()
class FLAPPYBIRD_API ABgActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABgActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RandomBackGround();
	
private:
	UPROPERTY()
	class UPaperSpriteComponent* BgComponent;
	
	UPROPERTY()
	class UPaperSprite* SunBgSource;
	
	UPROPERTY()
	class UPaperSprite* NightBgSource;
};
