// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ALandActor::ALandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	LandSpriteRender = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRender"));
	LandSpriteRender->SetupAttachment(RootComponent);

	LandSpriteRenderNext = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRenderNext"));
	LandSpriteRenderNext->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> LandSource(
		TEXT("PaperSprite'/Game/FlappyBird/Textures/Land/land_Sprite.land_Sprite'"));

	LandSpriteRender->SetSprite(LandSource.Object);
	LandSpriteRenderNext->SetSprite(LandSource.Object);

	Speed = 100.f;
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();

	//设置第二块的位置
	LandSpriteRenderNext->SetRelativeLocation(FVector(336, 0, 0));
}

void ALandActor::UpdateLandLocation(float DeltaTime)
{
	if (!LandSpriteRender || !LandSpriteRenderNext)
	{
		return;
	}

	float _Speed = Speed * DeltaTime * -1;

	//添加地板位移
	LandSpriteRender->AddLocalOffset(FVector(_Speed, 0, 0));
	LandSpriteRenderNext->AddLocalOffset(FVector(_Speed, 0, 0));

	if (LandSpriteRender->GetRelativeLocation().X < -336)
	{
		LandSpriteRender->SetRelativeLocation(FVector(LandSpriteRenderNext->GetRelativeLocation().X + 336, 0, 0));
	}

	if (LandSpriteRenderNext->GetRelativeLocation().X < -336)
	{
		LandSpriteRenderNext->SetRelativeLocation(FVector(LandSpriteRender->GetRelativeLocation().X + 336, 0, 0));
	}
}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLandLocation(DeltaTime);
}
