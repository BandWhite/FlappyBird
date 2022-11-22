// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdGameStateBase.h"

void ABirdGameStateBase::AddScore()
{
	Score++;
	UE_LOG(LogTemp, Log, TEXT("Score:%d"), Score);
}

void ABirdGameStateBase::ResetScore()
{
	Score = 0;
}

int32 ABirdGameStateBase::GetScore()
{
	return Score;
}
