// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TiGA_PlayerShoot.h"

#include "Actors/TiProjectileBase.h"
#include "Characters/TiConquistabot.h"
#include "Interfaces/TiTargetInterface.h"


UTiGA_PlayerShoot::UTiGA_PlayerShoot()
{
	AddedRange = 0.1f;
}

FVector UTiGA_PlayerShoot::AdjustRotation(AActor* TargetActor)
{
	AActor* Owner= GetOwningActorFromActorInfo();
	FVector PlayerLocation = Owner->GetActorLocation();
	FVector TargetLocation = ITiTargetInterface::Execute_GetTargetLocation(TargetActor);

	FRotator RotationXZ = FRotationMatrix::MakeFromX(TargetLocation - PlayerLocation).Rotator();
	FRotator ActorRotation = FRotator(Owner->GetActorRotation().Pitch, RotationXZ.Yaw, RotationXZ.Roll);
	Owner->SetActorRotation(ActorRotation);

	return TargetLocation;
}

void UTiGA_PlayerShoot::ActualShoot(FVector TargetLocation)
{
	ATiConquistabot* Owner = Cast<ATiConquistabot>(GetOwningActorFromActorInfo());

	if (Owner)
	{
		FVector MuzzleLocation = Owner->GetMesh()->GetSocketLocation(Socket);
		FTransform ProjectileTransform = FTransform(FRotationMatrix::MakeFromX(Owner->GetActorForwardVector()).Rotator(), MuzzleLocation);
		if (Owner->bIsLocking)
		{
			FRotator SpawnRotation = FRotationMatrix::MakeFromX(TargetLocation - MuzzleLocation).Rotator();
			ProjectileTransform = FTransform(SpawnRotation, MuzzleLocation);
		}

		ATiProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<ATiProjectileBase>(ProjectileClass, ProjectileTransform, GetOwningActorFromActorInfo());
		Projectile->Range = ProjectileRange;
		Projectile->FinishSpawning(ProjectileTransform);
	}
}
