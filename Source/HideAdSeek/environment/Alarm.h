// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SpotLightComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "Alarm.generated.h"

UCLASS()
class HIDEADSEEK_API AAlarm : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlarm();
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* SpotLight1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* SpotLight2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	URotatingMovementComponent* RotatingMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	 float LightDistance = 900;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void CalculateLightForLightSpot(USpotLightComponent* SpotLight);

};
