
#include "GG_BigSlime.h"
#include "GG_MiddleSlime.h"
#include "GG_SlimeMove.h"

AGG_BigSlime::AGG_BigSlime()
{
	CLASS_FINDER(AGG_MiddleSlime) BP_MiddleSlime = TEXT("/Game/Blueprints/GGBP_MiddleSlime");
	MiddleSlimeClass = BP_MiddleSlime.Class;
}

void AGG_BigSlime::Tick(float DeltaTime)
{
	if (bActivated)
		Super::Tick(DeltaTime);
}

float AGG_BigSlime::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
	{
		for (int i = 0; i < NumOfDivision; i++)
		{
			MiddleSlimeArray[i]->Init();
			MiddleSlimeArray[i]->GetStateMachine()->ChangeState(SGG_SlimeMove::GetInstance());
		}

		MiddleSlimeArray[0]->SetActorLocation(GetActorLocation() + FVector(0.0f, 20.0f, 0.0f));
		MiddleSlimeArray[1]->SetActorLocation(GetActorLocation() + FVector(0.0f, -20.0f, 0.0f));
	}

	return Damage;
}

void AGG_BigSlime::ClearSlime()
{
	SetActivated(false);

	for (int i = 0; i < MiddleSlimeArray.Num(); i++)
		MiddleSlimeArray[i]->ClearSlime();
}

void AGG_BigSlime::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumOfDivision; i++)
		MiddleSlimeArray.Add(GetWorld()->SpawnActor<AGG_MiddleSlime>(MiddleSlimeClass));
}
