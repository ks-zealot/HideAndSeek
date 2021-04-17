// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

#include "Enemy.generated.h"

UCLASS()
class HIDEADSEEK_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* LeftEye1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* RightEye1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* LeftEye2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	USpotLightComponent* RightEye2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	UAIPerceptionComponent* Sight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	UAIPerceptionComponent* Hearing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float DarkSightRange = 1500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float DefaultIntensity = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float DefaultRadius = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float SightIntensity = 20000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float SightRadius = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float HearingIntensity = 40000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float HearingRadius = 4000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float DefaultSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float SightSpeed = 1200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float HearingSpeed = 2400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float DefaultInnerConeAngle = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float SightInnerConeAngle= 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float HearingInnerConeAngle = 40;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void Reset();
private:
	UFUNCTION()
	void HandleSight(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void HandleHearing(AActor* Actor, FAIStimulus Stimulus);
	void SetEyes(float Intentcity, float Radius, float InnerConeAngle);
	void PlayStomp();
};
