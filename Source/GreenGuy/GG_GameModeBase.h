
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Array.h"
#include "GG_GameModeBase.generated.h"

UCLASS()
class GREENGUY_API AGG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGG_GameModeBase();

public:

	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
		void ChangeWidget(TSubclassOf<class UUserWidget> NewWidget);

	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintCallable)
		void InitGame();

	UFUNCTION(BlueprintImplementableEvent)
		void StageClear();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		class AGG_Player* GetPlayer() const;

	UFUNCTION(BlueprintCallable)
		class AGG_Phantom* GetPhantom() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()	FTimerHandle SpawnEnemyTimer;

	UPROPERTY() TSubclassOf<class AGG_Player> PlayerClass;

	UPROPERTY() TSubclassOf<class AGG_Phantom> PhantomClass;

	UPROPERTY() TSubclassOf<class AGG_Bat> BatClass;

	UPROPERTY() TSubclassOf<class AGG_BigSlime> SlimeClass;

	UPROPERTY() TSubclassOf<class AGG_Turtle> TurtleClass;

	UPROPERTY() class AGG_Player* Player;

	UPROPERTY() class AGG_Phantom* Phantom;

	TArray<TArray<class AGG_Enemy*>> EnemyObjectPool;

	UPROPERTY() class UUserWidget* CurrentWidget;

	UPROPERTY() int KindOfEnemyNum;
	UPROPERTY() int MaxEnemyNum;
	UPROPERTY() int CurrentEnemyNum;

	UPROPERTY() bool bPlaying;

	UPROPERTY(EditAnywhere) float MaxSpawnEnemyTime;
	UPROPERTY() float CurrentSpawnEnemyTime;

	UPROPERTY(EditAnywhere) float MinSpawnLocationX;
	UPROPERTY(EditAnywhere) float MinSpawnLocationY;
	UPROPERTY(EditAnywhere) float MaxSpawnLocationX;
	UPROPERTY(EditAnywhere) float MaxSpawnLocationY;

	UPROPERTY(EditAnywhere) int DistancePlayerWithEnemy;

};
