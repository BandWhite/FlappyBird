// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

#include "BgActor.h"
#include "BirdGameStateBase.h"
#include "BirdPawn.h"
#include "PipelineActor.h"
#include "Kismet/GameplayStatics.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	//设置启动pawn
	DefaultPawnClass = ABirdPawn::StaticClass();
	//设置GameState
	GameStateClass = ABirdGameStateBase::StaticClass();

	GameSpeed = 110.f;

	CurrentState = EGameState::EGS_Menu;
}

void AFlappyBirdGameModeBase::BeginPlay()
{
	//创建背景actor
	BgActor = GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(), FVector(0, -50, 0), FRotator::ZeroRotator);
	LandActor = GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(), FVector(0, 0, -270),
	                                               FRotator::ZeroRotator);

	PipelineActor = GetWorld()->SpawnActor<APipelineActor>(APipelineActor::StaticClass(), FVector(0, -2, 0),
	                                                       FRotator(0, 0, 0));
	BirdPawn = Cast<ABirdPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AFlappyBirdGameModeBase::ChangeState(EGameState State)
{
	switch (State)
	{
	case EGameState::EGS_Menu:
		BirdPawn->ChangeState(EBirdState::EBS_Idle);
		PipelineActor->ResetPieGroups();
		break;
	case EGameState::EGS_Gaming:
		LandActor->SetSpeed(GameSpeed);
		PipelineActor->SetSpeed(GameSpeed);
		BirdPawn->ChangeState(EBirdState::EBS_Fly);
		break;
	case EGameState::EGS_Over:
		LandActor->SetSpeed(0);
		PipelineActor->SetSpeed(0);
		BirdPawn->ChangeState(EBirdState::EBS_Dead);
		break;
	default:
		break;
	}
	CurrentState = State;
}

void AFlappyBirdGameModeBase::CMD(int32 cmd)
{
	ChangeState((EGameState)cmd);
}
