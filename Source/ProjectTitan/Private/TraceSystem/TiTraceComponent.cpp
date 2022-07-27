// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceSystem/TiTraceComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "DrawDebugHelpers.h"
#include "TiCharacter.h"


UTiTraceComponent::UTiTraceComponent()
{
	bDebugTraces = false;

	TraceDuration = 1.0f;
}


void UTiTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComp = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner(), false);
}

void UTiTraceComponent::ActivateTrace(FGameplayTag EventTag)
{
	FTimerDelegate Delegate;

	Delegate.BindUFunction(this, "ActualTrace", EventTag);

	FTracesWrapper* Data = Traces.Find(EventTag);

	float Period = 0.0f;
	if (Data)
	{
		Period = Data->Period;
	}
	
	GetWorld()->GetTimerManager().SetTimer(TraceHandle, Delegate, Period, true);
}

void UTiTraceComponent::DeactivateTrace()
{
	TraceHandle.Invalidate();
}

void UTiTraceComponent::ActualTrace(FGameplayTag EventTag)
{
	FTracesWrapper* Datas = Traces.Find(EventTag);
	
	if (Datas)
	{
		TArray<FTraceData> TraceArray = Datas->Traces;
		
		for (const FTraceData& Trace : TraceArray)
		{
			FName SocketName = Trace.SocketName;
			
			FVector StartLocation = SkeletalMeshComp->GetSocketLocation(SocketName);
			FQuat Rotation = SkeletalMeshComp->GetSocketQuaternion(SocketName);
			UWorld* World = GetWorld();

			if (Trace.Shape != ETraceShape::Remote)
			{
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
						break;
					}
				}
			}
			
			else
			{
				FActorSpawnParameters SpawnParams;
				FTransform SpawnTransform = FTransform(Rotation, StartLocation);
				
				World->SpawnActor<AActor>(Trace.RemoteTraceClass, SpawnTransform, SpawnParams);
			}
		}
	}
}
