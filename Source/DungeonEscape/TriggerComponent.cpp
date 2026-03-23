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
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover Actor is not valid"));
		return;
	}

	if (IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && !OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor does not have PressurePlateActivator tag!"));
		return;
	}

	ActivatorCount++;

	if (IsTriggered || ActivatorCount != 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger value is already triggered!"));
		return;
	}


	Trigger(true);
}


void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor) && !OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor does not have PressurePlateActivator tag!"));
		return;
	}

	ActivatorCount--;

	if (!IsTriggered || ActivatorCount != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger value is not triggered!"));
		return;
	}


	Trigger(false);
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;

	if (!IsValid(Mover))
	{
		UE_LOG(LogTemp, Warning, TEXT("MoverComponent not found!"));
		return;
	}

	Mover->SetMoveUp(IsTriggered);
}
