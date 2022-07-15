// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceSystem/TiTraceComponent.h"

#include "DrawDebugHelpers.h"
#include "TiCharacter.h"


UTiTraceComponent::UTiTraceComponent()
{
	bDebugTraces = false;
}


void UTiTraceComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTiTraceComponent::TraceByEventTag(USkeletalMeshComponent* SkeletalMeshComponent, FGameplayTag EventTag,
	FHitResult& OutHit)
{
	FTracesWrapper* Datas = Traces.Find(EventTag);
	
	if (Datas)
	{
		TArray<FTraceData> TraceArray = Datas->Traces;
		
		for (const FTraceData& Trace : TraceArray)
		{
			FCollisionShape Shape;
			
			FHitResult Hit;
			FVector StartLocation = SkeletalMeshComponent->GetSocketLocation(Trace.SocketName);
			FVector EndLocation;
			FQuat Rotation = SkeletalMeshComponent->GetSocketQuaternion(Trace.SocketName);
			FVector DebugCenterLocation;
			FCollisionObjectQueryParams ObjectQueryParams;

			UWorld* World = GetWorld();

			switch (Trace.Shape)
			{
			case ETraceShape::Box:
				Shape.SetBox(Trace.BoxExtent);
				EndLocation = StartLocation + (Rotation.Vector() * Trace.BoxExtent.X);
				if (bDebugTraces)
				{
					DebugCenterLocation = StartLocation + (Rotation.Vector() * Trace.BoxExtent.X / 2);
					DrawDebugBox(World, DebugCenterLocation, Trace.BoxExtent, Rotation, FColor::Red, false, 0.01);
				}
				break;
				
			case ETraceShape::Sphere:
				Shape.SetSphere(Trace.SphereRadius);
				if (bDebugTraces)
				{
					
				}
				DrawDebugSphere(World, StartLocation, Trace.SphereRadius, 16, FColor::Red, false, 0.01);
				break;
				
			case ETraceShape::Capsule:
				Shape.SetCapsule(Trace.CapsuleRadius, Trace.CapsuleHalfHeight);
				if (bDebugTraces)
				{
					EndLocation = StartLocation + (Rotation.Vector() * Trace.CapsuleHalfHeight);
					DebugCenterLocation = StartLocation + (Rotation.Vector() * Trace.CapsuleHalfHeight / 2);
					DrawDebugCapsule(World, StartLocation, Trace.CapsuleHalfHeight, Trace.CapsuleRadius, Rotation, FColor::Red, false, 0.01);
				}
				break;
			}
			
			
			ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
			World->SweepSingleByObjectType(Hit , StartLocation, EndLocation, Rotation, ObjectQueryParams, Shape);

			if(Hit.bBlockingHit)
			{
				//TODO Use Attribute
				OutHit = Hit;
				Cast<ATiCharacter>(Hit.GetActor())->GetDamage();
				break;
			}
		}
	}
}
