// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceSystem/TiTraceComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "DrawDebugHelpers.h"


UTiTraceComponent::UTiTraceComponent()
{
	bDebugTraces = false;

	TraceDuration = 1.0f;
}


void UTiTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComp = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}


void UTiTraceComponent::ActivateTrace(FGameplayTag EventTag)
{
	FTracesWrapper* Data = Traces.Find(EventTag);
	
	if (Data)
	{
		if (Data->RemoteTrace.RemoteTraceClass)
		{
			FRemoteTrace RemoteTrace = Data->RemoteTrace;
			
			FName SocketName = RemoteTrace.SocketName;
			
			FVector StartLocation = SkeletalMeshComp->GetSocketLocation(SocketName);
			FRotator Rotation = FRotator(0.0f, SkeletalMeshComp->GetSocketRotation(SocketName).Yaw, 0.0f); ;
			
			FTransform SpawnTransform = FTransform(Rotation, StartLocation);
			
			ATiRemoteTrace* RemoteTraceActor = GetWorld()->SpawnActorDeferred<ATiRemoteTrace>(RemoteTrace.RemoteTraceClass, SpawnTransform, GetOwner());
			RemoteTraceActor->SetRange(RemoteTrace.Range);
			RemoteTraceActor->SetSpeed(RemoteTrace.Speed);

			RemoteTraceActor->FinishSpawning(SpawnTransform);
		}

		if (Data->Traces.Num() > 0)
		{
			float Period = Data->Period;

			FTimerDelegate Delegate;

			Delegate.BindUFunction(this, "TraceElapsed", Data->Traces);

			GetWorld()->GetTimerManager().SetTimer(TraceHandle, Delegate, Period, true);
		}
	}
}


void UTiTraceComponent::DeactivateTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceHandle);
}


void UTiTraceComponent::TraceElapsed(TArray<FTraceData>& TraceArray)
{
	for (const FTraceData& Trace : TraceArray)
	{
		FName SocketName = Trace.SocketName;
		
		FVector StartLocation = SkeletalMeshComp->GetSocketLocation(SocketName);
		FQuat Rotation = SkeletalMeshComp->GetSocketQuaternion(SocketName);
		UWorld* World = GetWorld();
		
		FCollisionShape Shape;
	
		FHitResult Hit;
		
		FVector EndLocation;
		
		FVector DebugCenterLocation;
		FCollisionObjectQueryParams ObjectQueryParams;
		
		switch (Trace.Shape)
		{
		case ETraceShape::Box:
			Shape.SetBox(Trace.BoxExtent);
			EndLocation = StartLocation + (Rotation.Vector() * Trace.BoxExtent.X);
			if (bDebugTraces)
			{
				DebugCenterLocation = StartLocation + (Rotation.Vector() * Trace.BoxExtent.X / 2);
				DrawDebugBox(World, DebugCenterLocation, Trace.BoxExtent, Rotation, FColor::Red, false, TraceDuration);
			}
			break;
		
		case ETraceShape::Sphere:
			Shape.SetSphere(Trace.SphereRadius);
			if (bDebugTraces)
			{
				DrawDebugSphere(World, StartLocation, Trace.SphereRadius, 16, FColor::Red, false, TraceDuration);
			}
			break;
		
		case ETraceShape::Capsule:
			Shape.SetCapsule(Trace.CapsuleRadius, Trace.CapsuleHalfHeight);
			if (bDebugTraces)
			{
				EndLocation = StartLocation + (Rotation.Vector() * Trace.CapsuleHalfHeight);
				DebugCenterLocation = StartLocation + (Rotation.Vector() * Trace.CapsuleHalfHeight / 2);
				DrawDebugCapsule(World, StartLocation, Trace.CapsuleHalfHeight, Trace.CapsuleRadius, Rotation, FColor::Red, false, TraceDuration);
			}
			break;
			
		default:
			UE_LOG(LogTemp, Warning, TEXT("Case Undefined"))
			break;
		}
		
		ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
		World->SweepSingleByObjectType(Hit , StartLocation, EndLocation, Rotation, ObjectQueryParams, Shape);

		if(Hit.bBlockingHit)
		{
			UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Hit.GetActor());
			if (ASC)
			{
				ASC->BP_ApplyGameplayEffectToSelf(DamageEffect, 1, FGameplayEffectContextHandle());
				
				DeactivateTrace();
				break;
			}
		}
	}
}
