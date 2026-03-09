// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// PRATICA SUI PUNTATORI
	float MyFloat = 10.0f;
	float* FloatPtr = &MyFloat;
	
	float Result = *FloatPtr + 5;
	UE_LOG(LogTemp, Display, TEXT("Result: '%f'"), Result);
	
	*FloatPtr = 30.0f;
	UE_LOG(LogTemp, Display, TEXT("VALORI MyFloat: '%f' | *FloatPtr: '%f'"), MyFloat, *FloatPtr);
	UE_LOG(LogTemp, Display, TEXT("INDIRIZZI &MyFloat: '%p' | *FloatPtr: '%p'"), &MyFloat, FloatPtr);
	
	FVector MyVector = FVector::OneVector;
	FVector* VectorPtr = &MyVector;
	VectorPtr->X = 10.0f;
	VectorPtr->Y = 20.0f;
	VectorPtr->Z = 30.0f;
	
	FString LogStringPtr = VectorPtr->ToCompactString();
	UE_LOG(LogTemp, Display, TEXT("*VectorPtr: '%s'"), *LogStringPtr);
	
	
	AActor* OwnerActor = GetOwner();
	UE_LOG(LogTemp, Display, TEXT("Owner name or label: '%s'"), *OwnerActor->GetActorNameOrLabel());
	
	StartLocation = OwnerActor->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("StartLocation: '%s'"), *StartLocation.ToCompactString());
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	CurrentLocation.Z += 100 * DeltaTime; // 1 metro al secondo
	GetOwner()->SetActorLocation(CurrentLocation);
}

