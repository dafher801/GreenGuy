
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GG_PhantomBombArea.generated.h"

USTRUCT()
struct FGG_BombArea : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float MinX;
	UPROPERTY(EditAnywhere) float MinY;
	UPROPERTY(EditAnywhere) float MaxX;
	UPROPERTY(EditAnywhere) float MaxY;

	UPROPERTY(EditAnywhere) int WhenNeglectBombNum;
	UPROPERTY(EditAnywhere) int WhenHitBombNum;

	UPROPERTY(EditAnywhere) float MinDistanceBetweenBombs;

	UPROPERTY() TArray<class AGG_Projectile*> Bombs;
};

UCLASS()
class GREENGUY_API UGG_PhantomBombArea : public UObject
{
	GENERATED_BODY()
	
};
