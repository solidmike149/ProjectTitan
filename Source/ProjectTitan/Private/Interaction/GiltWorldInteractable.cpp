// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/GiltWorldInteractable.h"


AGiltWorldInteractable::AGiltWorldInteractable()
{

}

void AGiltWorldInteractable::GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery,
	FInteractionOptionBuilder& OptionBuilder)
{
	OptionBuilder.AddInteractionOption(Option);
}
