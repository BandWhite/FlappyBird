// Fill out your copyright notice in the Description page of Project Settings.


#include "PipelineActor.h"

#include "BirdGameStateBase.h"
#include "FlappyBirdGameModeBase.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APipelineActor::APipelineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	static ConstructorHelpers::FObjectFinder<UPaperSprite> Up(
		TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_down_Sprite.pipe_down_Sprite'")
	);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Down(
		TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_up_Sprite.pipe_up_Sprite'")
	);


	for (int32 i = 0; i < 3; ++i)
	{
		FString GroupName = FString::Printf(TEXT("Group%d"), i);
		USceneComponent* Group = CreateDefaultSubobject<USceneComponent>(*GroupName);

		FString UpPipeName = FString::Printf(TEXT("Pipe%d"), i * 2);
		UPaperSpriteComponent* UpComp = CreateDefaultSubobject<UPaperSpriteComponent>(*UpPipeName);

		FString DownPipeName = FString::Printf(TEXT("Pipe%d"), i * 2 + 1);
		UPaperSpriteComponent* DownComp = CreateDefaultSubobject<UPaperSpriteComponent>(*DownPipeName);

		Group->SetupAttachment(RootComponent);
		UpComp->SetupAttachment(Group);
		DownComp->SetupAttachment(Group);
		UpComp->SetSprite(Up.Object);
		DownComp->SetSprite(Down.Object);

		UpComp->SetRelativeLocation(FVector(0, 0, 220));
		DownComp->SetRelativeLocation(FVector(0, 0, -220));
		PipeGroups.Add(Group);
	}

	Speed = 0.f;
	GroupInterval = 190;
	bAddCoin = false;
}

// Called when the game starts or when spawned
void APipelineActor::BeginPlay()
{
	Super::BeginPlay();
	ResetPieGroups();
	CoinSound = LoadObject<USoundBase>(nullptr,TEXT("SoundWave'/Game/FlappyBird/Sounds/coin.coin'"));
}

void APipelineActor::ResetPieGroups()
{
	for (int32 i = 0; i < 3; ++i)
	{
		PipeGroups[i]->SetRelativeLocation(FVector(GroupInterval * i + 230, 0, 0));
		RandomPipeGroupZ(PipeGroups[i]);
	}
}

void APipelineActor::RandomPipeGroupZ(USceneComponent* PipeGroup)
{
	FVector OldPosition = PipeGroup->GetRelativeLocation();
	OldPosition.Z = FMath::RandRange(-90.f, 90.f);
	PipeGroup->SetRelativeLocation(OldPosition);
}

void APipelineActor::UpdatePipeGroupPosition(float DeltaTime)
{
	if (!Speed)
	{
		return;
	}

	float _Speed = Speed * DeltaTime * -1;


	for (int32 i = 0; i < 3; ++i)
	{
		PipeGroups[i]->AddLocalOffset(FVector(_Speed, 0, 0));
		if (PipeGroups[i]->GetRelativeLocation().X < -90 && !bAddCoin)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CoinSound);
			bAddCoin = true;
			AFlappyBirdGameModeBase* CurrentGm = Cast<AFlappyBirdGameModeBase>(GetWorld()->GetAuthGameMode());
			if (CurrentGm)
			{
				ABirdGameStateBase* GameStateBase = CurrentGm->GetGameState<ABirdGameStateBase>();
				if (GameStateBase)
				{
					GameStateBase->AddScore();
				}
			}
		}

		if (PipeGroups[i]->GetRelativeLocation().X < -144)
		{
			int32 Index = i - 1;
			if (Index < 0)
			{
				Index = 2;
			}
			PipeGroups[i]->SetRelativeLocation(
				FVector(PipeGroups[Index]->GetRelativeLocation().X + GroupInterval, 0, 0));
			RandomPipeGroupZ(PipeGroups[i]);
			bAddCoin = false;
		}
	}
}


// Called every frame
void APipelineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePipeGroupPosition(DeltaTime);
}

void APipelineActor::SetSpeed(float NewSpeed)
{
	this->Speed = NewSpeed;
}
