// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateWithLight.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlateWithLight::APlateWithLight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComponent->SetupAttachment(GetStaticMeshComponent());
	SpotLightComponent->SetVisibility(true);
}

// Called when the game starts or when spawned
void APlateWithLight::BeginPlay()
{
	Super::BeginPlay();
	/*if (UKismetMathLibrary::Greater_FloatFloat(UKismetMathLibrary::RandomFloat(), LightChance))
	{
		SpotLightComponent->SetVisibility(true);
		bAmIGetLight = true;
	}*/
}

// Called every frame
void APlateWithLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
