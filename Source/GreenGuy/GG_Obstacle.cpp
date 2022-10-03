
#include "GG_Obstacle.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

AGG_Obstacle::AGG_Obstacle()
{
	Tags.Add("Obstacle");

	ShapeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion"));
	RootComponent = ShapeCollision;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);
}

void AGG_Obstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AGG_Obstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
