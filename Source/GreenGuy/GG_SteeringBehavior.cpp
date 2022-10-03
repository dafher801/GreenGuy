
#include "GG_SteeringBehavior.h"
#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"

FGG_SteeringBehavior::FGG_SteeringBehavior(AActor* Object, UMovementComponent* ObjectMovement)
    : Actor(Object), Movement(ObjectMovement)
{

}

AActor* FGG_SteeringBehavior::GetActor() const
{
    return Actor;
}

FVector FGG_SteeringBehavior::Move(FRotator TargetRotation)
{
    TargetRotation.Pitch = 0.0f;
    TargetRotation.Roll = 0.0f;
	return TargetRotation.Vector() * Movement->GetMaxSpeed();
}

FVector FGG_SteeringBehavior::Seek(FVector TargetLocation)
{
    TargetLocation.Z = 0.0f;
	FVector Vector = TargetLocation - Actor->GetActorLocation();

	return Vector.GetSafeNormal(Movement->GetMaxSpeed() / 10.0f) * Movement->GetMaxSpeed();
}

FVector FGG_SteeringBehavior::Pursuit(FVector EvaderPosition, FVector EvaderVelocity)
{
    float EvaderVelocityLength = FVector::Dist(FVector::ZeroVector, EvaderVelocity);
    float Time = EvaderVelocityLength != 0.0f ? FVector::Dist(
        EvaderPosition, Actor->GetActorLocation()) / EvaderVelocityLength : 0.0f;

    FVector TargetPosition = (EvaderVelocity * Time) + EvaderPosition;

    if (FVector::Dist(TargetPosition, Actor->GetActorLocation()) <=
        FVector::Dist(TargetPosition, EvaderPosition))
    {
        return Seek(EvaderPosition);
    }

    return Seek(TargetPosition);
}
