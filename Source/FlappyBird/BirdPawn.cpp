// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABirdPawn::ABirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//组件根节点
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//渲染能力节点
	UPaperFlipbookComponent* FlipBookComponent =  CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBookComponent"));

	//渲染节点附到根节点
	FlipBookComponent->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

