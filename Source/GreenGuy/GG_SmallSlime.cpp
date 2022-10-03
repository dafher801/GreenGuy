
#include "GG_SmallSlime.h"

AGG_SmallSlime::AGG_SmallSlime()
{
	SetActivated(false);
}

void AGG_SmallSlime::Tick(float DeltaTime)
{
	if (bActivated)
		Super::Tick(DeltaTime);
}

void AGG_SmallSlime::BeginPlay()
{
	Super::BeginPlay();
}
