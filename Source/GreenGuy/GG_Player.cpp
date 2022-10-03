
#include "GG_Player.h"
#include "GG_PlayerWeapon.h"
#include "GG_PlayerIdle.h"
#include "GG_PlayerMove.h"
#include "GG_GameModeBase.h"
#include "GG_ObjectDataTable.h"
#include "GG_SteeringBehavior.h"
#include "Components/ShapeComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

AGG_Player::AGG_Player()
{
	Tags.Add("Player");

	Weapon = CreateDefaultSubobject<UGG_PlayerWeapon>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	StateMachine = new TGG_StateMachine<AGG_Player>(this);

	BaseStatus = FGG_Status(500.0f, 100.0f, 2.0f, 0.0f, 500.0f, 1000.0f);
	CurrentStatus = BaseStatus;
}

void AGG_Player::Init()
{
	Super::Init();

	StateMachine->ChangeState(SGG_PlayerIdle::GetInstance());
}

void AGG_Player::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
		StateMachine->Execute();
	}
}

void AGG_Player::Idle(float DeltaTime)
{
	MoveVector = FVector(CurrentMoveUpDownValue, CurrentMoveLeftRightValue, 0.0f);

	if (CurrentMoveUpDownValue != 0.0f || CurrentMoveLeftRightValue != 0.0f)
	{
		StateMachine->ChangeState(SGG_PlayerMove::GetInstance());
		return;
	}

	Aim();
	Fire(DeltaTime);
}

void AGG_Player::Move(float DeltaTime)
{
	MoveVector = FVector(CurrentMoveUpDownValue, CurrentMoveLeftRightValue, 0.0f);

	if (MoveVector == FVector::ZeroVector)
	{
		StateMachine->ChangeState(SGG_PlayerIdle::GetInstance());
		return;
	}

	Movement->Velocity = SteeringBehavior->Move(MoveVector.Rotation());

	Aim();
	Fire(DeltaTime);
}

void AGG_Player::Aim()
{
	if (CurrentAttackLeftRightValue > 0.0f)
		Flipbook->SetFlipbook(LeftFlipbook);
	else if (CurrentAttackLeftRightValue < 0.0f)
		Flipbook->SetFlipbook(RightFlipbook);

	if (Weapon)
		Weapon->Aim(FVector(-1 * CurrentAttackUpDownValue, CurrentAttackLeftRightValue, 0.0f).Rotation());
}

void AGG_Player::Fire(float DeltaTime)
{
	if (CurrentAttackUpDownValue != 0.0f || CurrentAttackLeftRightValue != 0.0f)
		Super::Fire(DeltaTime);
}

void AGG_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveUpDown", this, &AGG_Player::InputMoveUpDownValue);
	InputComponent->BindAxis("MoveLeftRight", this, &AGG_Player::InputMoveLeftRightValue);
	InputComponent->BindAxis("AttackUpDown", this, &AGG_Player::InputAttackUpDownValue);
	InputComponent->BindAxis("AttackLeftRight", this, &AGG_Player::InputAttackLeftRightValue);
}

float AGG_Player::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;
	CurrentStatus.HP -= DamageAmount;

	if (CurrentStatus.HP <= 0.0f)
	{
		CurrentStatus.HP = 0.0f;

		Cast<AGG_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
	}

	return DamageAmount;
}

void AGG_Player::SetPlayerIdleFlipbook()
{
	LeftFlipbook = LeftIdleFlipbook;
	RightFlipbook = RightIdleFlipbook;

	if (Flipbook->GetFlipbook() == LeftMoveFlipbook)
		Flipbook->SetFlipbook(LeftFlipbook);
	else
		Flipbook->SetFlipbook(RightFlipbook);
}

void AGG_Player::SetPlayerMoveFlipbook()
{
	LeftFlipbook = LeftMoveFlipbook;
	RightFlipbook = RightMoveFlipbook;

	if (Flipbook->GetFlipbook() == LeftIdleFlipbook)
		Flipbook->SetFlipbook(LeftFlipbook);
	else
		Flipbook->SetFlipbook(RightFlipbook);
}

void AGG_Player::BeginPlay()
{
	Super::BeginPlay();

	StateMachine->Enter();
}

void AGG_Player::InputMoveUpDownValue(float InputValue)
{
	CurrentMoveUpDownValue = InputValue;
}

void AGG_Player::InputMoveLeftRightValue(float InputValue)
{
	CurrentMoveLeftRightValue = InputValue;
}

void AGG_Player::InputAttackUpDownValue(float InputValue)
{
	CurrentAttackUpDownValue = InputValue;
}

void AGG_Player::InputAttackLeftRightValue(float InputValue)
{
	CurrentAttackLeftRightValue = InputValue;
}

TGG_StateMachine<AGG_Player>* AGG_Player::GetStateMachine() const
{
	return StateMachine;
}
