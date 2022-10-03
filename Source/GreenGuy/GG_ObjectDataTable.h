
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GG_ObjectDataTable.generated.h"

#define CLASS_FINDER(ClassType) static ConstructorHelpers::FClassFinder<ClassType>
#define OBJECT_FINDER(ObjectType) static ConstructorHelpers::FObjectFinder<ObjectType>

USTRUCT()
struct FGG_Status : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Range;

	FORCEINLINE FGG_Status() {}

	FORCEINLINE FGG_Status(float HP, float ATK, float AttackSpeed, float DEF, float MoveSpeed, float Range)
		: HP(HP), ATK(ATK), AttackSpeed(AttackSpeed), DEF(DEF), MoveSpeed(MoveSpeed), Range(Range) {}

	FORCEINLINE FGG_Status(const FGG_Status& Status)
		: HP(Status.HP)
		, ATK(Status.ATK)
		, AttackSpeed(Status.AttackSpeed)
		, DEF(Status.DEF)
		, MoveSpeed(Status.MoveSpeed)
		, Range(Status.Range) {}

	FORCEINLINE FGG_Status& operator=(const FGG_Status& Status)
	{
		HP = Status.HP;
		ATK = Status.ATK;
		AttackSpeed = Status.AttackSpeed;
		DEF = Status.DEF;
		MoveSpeed = Status.MoveSpeed;
		Range = Status.Range;

		return *this;
	}

	FORCEINLINE struct FGG_Status operator*(float Ratio)
	{
		FGG_Status ret;

		ret.HP = HP * Ratio;
		ret.ATK = ATK * Ratio;
		ret.AttackSpeed = AttackSpeed * Ratio;
		ret.DEF = DEF * Ratio;
		ret.MoveSpeed = MoveSpeed * Ratio;
		ret.Range = Range * Ratio;

		return ret;
	}

	FORCEINLINE struct FGG_Status& operator+=(const FGG_Status& Status)
	{
		HP += Status.HP;
		ATK += Status.ATK;
		DEF += Status.DEF;
		MoveSpeed += Status.MoveSpeed;
		AttackSpeed += Status.AttackSpeed;
		Range += Status.Range;

		return *this;
	}
};

UCLASS()
class GREENGUY_API UGG_ObjectDataTable : public UObject
{
	GENERATED_BODY()
};
