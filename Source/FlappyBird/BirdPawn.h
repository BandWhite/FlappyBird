// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPawn.generated.h"

namespace EBirdState
{
	enum Type
	{
		EBS_Idle,
		EBS_Fly,
		EBS_Dead,
	};
}


UCLASS()
class FLAPPYBIRD_API ABirdPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DoJump();

	void Init();

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void UpdateFace();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeState(EBirdState::Type State);
	
protected:
	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* FlipBookComponent;

	EBirdState::Type CurrentState;

	UPROPERTY()
	class USoundBase* FlySound;
	
};
