// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(MoverActor))
	{
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (!IsValid(Mover))
		{
			UE_LOG(LogTemp, Warning, TEXT("MoverComponent not found!"));
			return;
		}
		
		Mover->bMoveUp = true;
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover Actor is not valid"));
		return;
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
