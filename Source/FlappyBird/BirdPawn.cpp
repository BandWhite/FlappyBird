// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "Kismet/GameplayStatics.h"

// Sets default values 
ABirdPawn::ABirdPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//组件根节点
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//渲染能力节点
	FlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBookComponent"));

	//渲染节点附到根节点
	FlipBookComponent->SetupAttachment(RootComponent);

	//移动鸟的位置靠后
	FlipBookComponent->SetRelativeLocation(FVector(-80, 0, 0));

	//导入鸟的动画资源
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> BirdFlipBook(
		TEXT("PaperFlipbook'/Game/FlappyBird/FlipBooks/Birds/PFB_BlueBird.PFB_BlueBird'"));
	if (BirdFlipBook.Object)
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
	//相机视口大小
	CameraComponent->OrthoWidth = 1000;

	//调整相机旋转
	SpringArmComponent->SetRelativeRotation(FRotator(0, -90, 0));

	//关闭摄像机的碰撞测试
	SpringArmComponent->bDoCollisionTest = false;

	CurrentState = EBirdState::EBS_Idle;
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ABirdPawn::DoJump()
{
	if (CurrentState == EBirdState::EBS_Idle)
	{
		ChangeState(EBirdState::EBS_Fly);
	}
	//移除原有力
	FlipBookComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);

	//添加力
	FlipBookComponent->AddImpulse(FVector(0, 0, 2000));

	//播放声音
	UGameplayStatics::PlaySound2D(GetWorld(), FlySound);
}

void ABirdPawn::Init()
{
	FlipBookComponent->OnComponentHit.AddDynamic(this, &ABirdPawn::OnComponentHit);
	FlipBookComponent->GetBodyInstance()->bNotifyRigidBodyCollision = true; //开启物理通知
	FlipBookComponent->SetCollisionObjectType(ECC_Pawn); //设置碰撞类型

	FlySound = LoadObject<USoundBase>(nullptr,TEXT("SoundWave'/Game/FlappyBird/Sounds/fly.fly'"));

	//设置物理锁定
	FBodyInstance* BodyInstance = FlipBookComponent->GetBodyInstance();
	if (BodyInstance)
	{
		BodyInstance->bLockXRotation = true;
		BodyInstance->bLockZRotation = true;

		BodyInstance->bLockXTranslation = true;
		BodyInstance->bLockYTranslation = true;

		BodyInstance->CreateDOFLock();//调用锁定
	}
}

void ABirdPawn::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("TTTTTTTTTTTTTTTTTTT"))
}

void ABirdPawn::UpdateFace()
{
	if (CurrentState != EBirdState::EBS_Fly)
	{
		return;
	}

	FVector Velocity = FlipBookComponent->GetPhysicsLinearVelocity(); //获取鸟当前的速度
	FlipBookComponent->SetRelativeRotation(FRotator(FMath::Clamp<float>(Velocity.Z * 0.1f, -90, 90), 0, 0));
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFace();
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定输入事件
	PlayerInputComponent->BindAction(TEXT("DoJump"), IE_Pressed, this, &ABirdPawn::DoJump);
}

void ABirdPawn::ChangeState(EBirdState::Type State)
{
	switch (State)
	{
	case EBirdState::EBS_Idle:
		break;
	case EBirdState::EBS_Fly:
		//开启虚拟物理
		FlipBookComponent->SetSimulatePhysics(true);
		break;
	case EBirdState::EBS_Dead:
		break;
	default:
		break;
	}
	CurrentState = State;
}
