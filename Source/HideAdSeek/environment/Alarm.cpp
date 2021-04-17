// Fill out your copyright notice in the Description page of Project Settings.


#include "Alarm.h"


#include "HideAdSeek/player/PlayableCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAlarm::AAlarm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	SpotLight1 = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light 1"));
	SpotLight2 = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light 2"));
	SpotLight1->SetupAttachment(RootComponent);
	SpotLight2->SetupAttachment(RootComponent);
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

// Called when the game starts or when spawned
void AAlarm::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAlarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateLightForLightSpot(SpotLight1);
	CalculateLightForLightSpot(SpotLight2);
}

void AAlarm::CalculateLightForLightSpot(USpotLightComponent* SpotLight)
{
	FVector Location = SpotLight->GetComponentLocation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetActorRotation()) * LightDistance;
	FHitResult HitResult;
	 
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, ForwardVector, ECC_GameTraceChannel2))
	{
		APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(HitResult.Actor);

		if (PlayableCharacter)
		{
			 PlayableCharacter->EnlightMe();
		}  
	}  
}
