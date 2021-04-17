// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SpotLightComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "PlateWithLight.generated.h"

UCLASS()
class HIDEADSEEK_API APlateWithLight : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlateWithLight();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* SpotLightComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
