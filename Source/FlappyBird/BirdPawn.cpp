// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"

// Sets default values
ABirdPawn::ABirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//组件根节点
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//渲染能力节点
	FlipBookComponent =  CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBookComponent"));

	//渲染节点附到根节点
	FlipBookComponent->SetupAttachment(RootComponent);

	//导入鸟的动画资源
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> BirdFlipBook(TEXT("PaperFlipbook'/Game/FlappyBird/FlipBooks/Birds/PFB_BlueBird.PFB_BlueBird'"));
	if(BirdFlipBook.Object)
	{
		FlipBookComponent->SetFlipbook(BirdFlipBook.Object);
	}
	
	//构建相机
	//构建吊臂
	USpringArmComponent* SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	//构建相机
	UCameraComponent* CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	//相机改为正交模式
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	
	//调整相机旋转
	SpringArmComponent->SetRelativeRotation(FRotator(0,-90,0));
	//关闭摄像机的碰撞测试
	SpringArmComponent->bDoCollisionTest = false;
	
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

