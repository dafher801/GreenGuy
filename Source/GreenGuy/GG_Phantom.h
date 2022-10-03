
#pragma once

#include "CoreMinimal.h"
#include "GG_Enemy.h"
#include "GG_StateMachine.h"
#include "GG_Phantom.generated.h"

UCLASS()
class GREENGUY_API AGG_Phantom : public AGG_Enemy
{
	GENERATED_BODY()
	
public:

	AGG_Phantom();

public:

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	TGG_StateMachine<AGG_Phantom>* GetStateMachine() const;

	void RoundPattern(float DeltaTime);
	void ReadyForRoundPattern(float DeltaTime);
	float GetRoundAttackSpeed() const;

	void BombPattern(float DeltaTime);
	void ReadyForBombPattern(float DeltaTime);
	float GetBombAttackSpeed() const;

	void ShotPattern(float DeltaTime);
	float GetShotAttackSpeed() const;

	void SeekPattern(float DeltaTime);
	float GetSeekMovementSpeed() const;

	void SnowingPattern(float DeltaTime);
	void ReadyForSnowingPattern(float DeltaTime);
	float GetSnowingAttackSpeed() const;

	void SpawnEnemy(float DeltaTime);
	float GetSpawnTime() const;

	void CheckMagicCircle(class UPaperFlipbook* MagicCircle);

	void MagicCircleSetFlipbook(class UPaperFlipbook* MagicCircle);

protected:

	virtual void BeginPlay() override;

	virtual void Move() override;
	virtual void Aim() override;
	virtual void Fire(float DeltaTime) override;

protected:

	TGG_StateMachine<AGG_Phantom>* StateMachine;

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* MagicCircleFlipbook;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* RoundMagicCircle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* BombMagicCircle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) class UPaperFlipbook* SnowingMagicCircle;

	UPROPERTY(EditAnywhere) float RoundAttackSpeed;
	UPROPERTY() float TimeElapsedSinceRound;

	UPROPERTY(EditAnywhere) float BombAttackSpeed;
	UPROPERTY() float TimeElapsedSinceBomb;

	UPROPERTY(EditAnywhere) float SnowingAttackSpeed;
	UPROPERTY(EditAnywhere) float ShotAttackSpeed;
	UPROPERTY(EditAnywhere) float MaxShotTime;
	UPROPERTY() float TimeElapsedSinceSnowing;
	UPROPERTY() float TimeElapsedSinceShot;
	UPROPERTY() float CurrentShotTime;

	UPROPERTY(EditAnywhere) float MinDistanceWithPlayer;
	UPROPERTY(EditAnywhere) float SeekMovementSpeed;
	UPROPERTY(EditAnywhere) float MaxSeekTime;
	UPROPERTY() float CurrentSeekTime;

	UPROPERTY(EditAnywhere) float SpawnTime;
	UPROPERTY() float TimeElapsedSinceSpawn;

};
