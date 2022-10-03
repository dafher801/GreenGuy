
#include "GG_MiddleSlime.h"
#include "GG_SmallSlime.h"

AGG_MiddleSlime::AGG_MiddleSlime()
{
	CLASS_FINDER(AGG_SmallSlime) BP_SmallSlime = TEXT("/Game/Blueprints/GGBP_SmallSlime");
	SmallSlimeClass = BP_SmallSlime.Class;
}

void AGG_MiddleSlime::Tick(float DeltaTime)
{
	if (bActivated)
		Super::Tick(DeltaTime);
}

float AGG_MiddleSlime::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
	{
		for (int i = 0; i < NumOfDivision; i++)
			SmallSlimeArray[i]->Init();

		SmallSlimeArray[0]->SetActorLocation(GetActorLocation() + FVector(0.0f, 20.0f, 0.0f));
		SmallSlimeArray[1]->SetActorLocation(GetActorLocation() + FVector(0.0f, -20.0f, 0.0f));
	}

	return Damage;
}

void AGG_MiddleSlime::ClearSlime()
{
	SetActivated(false);

	for (int i = 0; i < SmallSlimeArray.Num(); i++)
		SmallSlimeArray[i]->SetActivated(false);
}

void AGG_MiddleSlime::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumOfDivision; i++)
		SmallSlimeArray.Add(GetWorld()->SpawnActor<AGG_SmallSlime>(SmallSlimeClass));
}
