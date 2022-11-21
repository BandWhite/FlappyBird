// Fill out your copyright notice in the Description page of Project Settings.


#include "BgActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ABgActor::ABgActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//创建Bg渲染组件
	BgComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgComponent"));
	//设置为根组件
	SetRootComponent(BgComponent);
}

// Called when the game starts or when spawned
void ABgActor::BeginPlay()
{
	Super::BeginPlay();
	RandomBackGround();
}

// Called every frame
void ABgActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABgActor::RandomBackGround()
{
	if (!SunBgSource)
	{
		SunBgSource = LoadObject<UPaperSprite>(
			nullptr,TEXT("PaperSprite'/Game/FlappyBird/Textures/Bg/bg_day_Sprite.bg_day_Sprite'"));
	}
	if (!NightBgSource)
	{
		NightBgSource = LoadObject<UPaperSprite>(
			nullptr,TEXT("PaperSprite'/Game/FlappyBird/Textures/Bg/bg_night_Sprite.bg_night_Sprite'"));
	}

	if (!BgComponent || !SunBgSource || !NightBgSource)
	{
		return;
	}

	UPaperSprite* CurrentBgSource = FMath::RandRange(0, 1) == 0 ? SunBgSource : NightBgSource;

	BgComponent->SetSprite(CurrentBgSource);
}
