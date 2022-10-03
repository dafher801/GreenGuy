
#pragma once

#include "CoreMinimal.h"

class FGG_SteeringBehavior
{
public:

	FGG_SteeringBehavior(class AActor* Object, class UMovementComponent* ObjectMovement);

public:

	class AActor* GetActor() const;

	FVector Move(FRotator TargetRotation);

	FVector Seek(FVector TargetLocation);

	FVector Pursuit(FVector EvaderPosition, FVector EvaderVelocity);

private:

	class AActor* Actor;

	class UMovementComponent* Movement;

};
