// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &AMyActor::Move, 1.0f, true, 1.0f);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveInTick();
}

void AMyActor::MoveInTick()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 1.0f);
	SetActorLocation(NewLocation);
}

void AMyActor::Move()
{
	TargetLocation = Step();
	FString TargetLocationString = TargetLocation.ToString();

	FVector CurrentLocation = GetActorLocation();
	FString CurrentLocationString = CurrentLocation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("CurrentLocation: %s"), *CurrentLocationString);
	UE_LOG(LogTemp, Warning, TEXT("TargetLocation: %s"), *TargetLocationString);
}

FVector AMyActor::Step()
{
	auto frontValue = FMath::RandRange(-100.0f, 100.0f);
	auto rightValue = FMath::RandRange(-100.0f, 100.0f);
	FVector Offset(frontValue, rightValue, 0.0f);
	FVector ResultLocation = GetActorLocation() + Offset;
	return ResultLocation;
}

