// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TiRemoteTrace.h"
#include "Components/ActorComponent.h"
#include "TiTraceComponent.generated.h"

class UGameplayEffect;
UENUM(BlueprintType)
enum class ETraceShape : uint8
{
	Box,
	Sphere,
	Capsule
};

USTRUCT(BlueprintType)
struct FTraceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETraceShape Shape;

	/* The socket from which we originate the trace */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, meta = (EditCondition= "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Shape==ETraceShape::Sphere", EditConditionHides))
	float SphereRadius;

	UPROPERTY(EditAnywhere, meta = (EditCondition= "Shape==ETraceShape::Box", EditConditionHides))
	FVector BoxExtent;
};


USTRUCT(BlueprintType)
struct FRemoteTrace
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName SocketName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATiRemoteTrace> RemoteTraceClass;

	UPROPERTY(EditAnywhere)
	float Range;

	UPROPERTY(EditAnywhere)
	float Speed = 100;
};


USTRUCT(BlueprintType)
struct FTracesWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (TitleProperty = "SocketName"))
	TArray<FTraceData> Traces;

	/* Time between 'ticks' to draw Traces */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Period = 0.01;

	UPROPERTY(EditAnywhere)
	FRemoteTrace RemoteTrace;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTITAN_API UTiTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTiTraceComponent();

protected:

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	TMap<FGameplayTag, FTracesWrapper> Traces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	bool bDebugTraces;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Traces", meta = (EditCondition = "bDebugTraces", EditConditionHides))
	float TraceDuration;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;

	FTimerHandle TraceHandle;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ActivateTrace(FGameplayTag EventTag);
	
	UFUNCTION(BlueprintCallable)
	void DeactivateTrace();

	UFUNCTION()
	void TraceElapsed(TArray<FTraceData>& TraceArray);
};
