// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/TiAnimNotifyState_Tracking.h"

#include "AI/TiAiCharacter.h"

void UTiAnimNotifyState_Tracking::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	ATiAiCharacter* AICharacter = Cast<ATiAiCharacter>(MeshComp->GetOwner());

	if (InterpSpeedCurve.GetRichCurveConst() && InterpSpeedCurve.GetRichCurveConst()->GetNumKeys() > 0)
	{
		Time += FrameDeltaTime;
		
		float Speed = InterpSpeedCurve.GetRichCurveConst()->Eval(Time);

		if(AICharacter)
		{
			AICharacter->Tracking(Speed);
		}
	}
	else
	{
		if(AICharacter)
		{
			AICharacter->Tracking(InterpSpeed);
		}
	}
}
