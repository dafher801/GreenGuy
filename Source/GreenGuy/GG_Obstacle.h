
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GG_Obstacle.generated.h"

UCLASS()
class GREENGUY_API AGG_Obstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	AGG_Obstacle();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere) class UShapeComponent* ShapeCollision;

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* Flipbook;

};
