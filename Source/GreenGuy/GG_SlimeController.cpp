
#include "GG_SlimeController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AGG_SlimeController::AGG_SlimeController()
{

}

void AGG_SlimeController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGG_SlimeController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();

	FNavLocation NextLocation;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
	}
}
