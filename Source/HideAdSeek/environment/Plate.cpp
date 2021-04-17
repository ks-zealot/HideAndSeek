// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"


#include "DrawDebugHelpers.h"
#include "Pickable.h"
#include "PlateWithLight.h"
#include "HideAdSeek/player/PlayableCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AISense_Hearing.h"


APlate::APlate()
{
	Alarm = CreateDefaultSubobject<UChildActorComponent>(TEXT("Alarm"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Alarm->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);
}

void APlate::Overlap(AActor* OtherActor)
{
	APlayableCharacter* Char = Cast<APlayableCharacter>(OtherActor);
	if (Char)
	{
		Char->bAmIOnLight = bAmIOnLight;
	}
	APickable* Pickable = Cast<APickable>(OtherActor);
	if (Pickable)
	{
		if (Pickable->bAmITaken)
		{
			UE_LOG(LogTemp, Log, TEXT("Bam"))
			UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this, MaxThrowNoiseRange, FName());
		}
		Pickable->bAmITaken = false;
	}
}

void APlate::EndOverlap(AActor* OtherActor)
{
	APlayableCharacter* Char = Cast<APlayableCharacter>(OtherActor);
	if (Char)
	{
		Char->bAmIOnLight = false;
	}
}

void APlate::BeginPlay()
{
	Super::BeginPlay();
	CheckAmIOnLight();
	SpawnEnemy();
	SpawnCubes();
	SpawnPickable();
}

void APlate::CheckAmIOnLight()
{
	FHitResult HitResult;
	FVector End = GetActorLocation() + FVector(0, 0, RoomHeight);
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(),
	                                         End,
	                                         ECC_GameTraceChannel1, Params))
	{
		APlateWithLight* PlateWithLight = Cast<APlateWithLight>(HitResult.Actor);
		if (PlateWithLight)
		{
		//	bAmIOnLight = PlateWithLight->bAmIGetLight;
		}
	}
}

void APlate::SpawnEnemy()
{
	GetWorld()->SpawnActor<ACharacter>(EnemyBlueprint, UKismetMathLibrary::MakeTransform(GetActorLocation() +
		                                   FVector(UKismetMathLibrary::RandomFloatInRange(-1000, 1000),
		                                   	UKismetMathLibrary::RandomFloatInRange(-1500, 1500), 100), FRotator::ZeroRotator,
		                                   FVector::OneVector));
}

void APlate::SpawnPickable()
{
	for (int32 i = 0; i < NumberOfPickableCubes; i++)
	{
		MakeSpawnTry(FVector(10, 10, 10), PickableBlueprint);
	}
}

void APlate::SpawnCubes()
{
	for (int32 i = 0; i < NumberOfCubes; i++)
	{
		MakeSpawnTry(FVector(150.0, 150.0, 150.0), CubeBlueprint);
	}
}

FVector APlate::GetRandomPoint(float Height)
{
	return GetActorLocation() + FVector(UKismetMathLibrary::RandomFloatInRange(MinRange, MaxRange),
	                                    UKismetMathLibrary::RandomFloatInRange(MinRange, MaxRange),
	                                    Height);
}

bool APlate::CanSpawnHere(FVector Point, FVector BoxSize)
{
	FHitResult HitResult;
	return !UKismetSystemLibrary::BoxTraceSingle(this, Point, Point,
	                                             BoxSize, FRotator::ZeroRotator,
	                                             UEngineTypes::ConvertToTraceType(ECC_Visibility),
	                                             false, TArray<AActor*>(), EDrawDebugTrace::None,
	                                             HitResult, true,
	                                             FLinearColor::Green, FLinearColor::Red, 0.0f);
}


void APlate::MakeSpawnTry(FVector ActorSize, TSubclassOf<AActor> ActorToSpawn)
{
	int32 TryCount = 0;
	int32 MaxTryCount = 3;
	FVector RandomPoint;
	while (TryCount < MaxTryCount)
	{
		RandomPoint = GetRandomPoint(ActorSize.Z);
		RandomPoint.Z = RandomPoint.Z + PlateHeight;
		if (CanSpawnHere(RandomPoint, ActorSize))
		{
			FTransform Transform = UKismetMathLibrary::MakeTransform(RandomPoint, FRotator::ZeroRotator,
			                                                         FVector::OneVector);
			GetWorld()->SpawnActor<AStaticMeshActor>(ActorToSpawn.Get(), Transform);
			return;
		}
		else
		{
			TryCount++;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Could not spawn"))
}
