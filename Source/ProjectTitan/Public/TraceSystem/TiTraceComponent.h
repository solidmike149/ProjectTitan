// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "TiTraceComponent.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (EditCondition= "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Shape==ETraceShape::Sphere", EditConditionHides))
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (EditCondition= "Shape==ETraceShape::Box", EditConditionHides))
	FVector BoxExtent;
};

USTRUCT(BlueprintType)
struct FTracesWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTraceData> Traces;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTITAN_API UTiTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTiTraceComponent();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	TMap<FGameplayTag, FTracesWrapper> Traces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traces")
	bool bDebugTraces;

	UFUNCTION(BlueprintCallable)
	void TraceByEventTag(USkeletalMeshComponent* SkeletalMeshComponent, FGameplayTag EventTag, float DeltaTime, FHitResult& OutHit);
};
