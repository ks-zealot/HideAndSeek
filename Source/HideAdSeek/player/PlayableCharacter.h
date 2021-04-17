// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Twin.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "PlayableCharacter.generated.h"

UCLASS()
class HIDEADSEEK_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float CrouchSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float NormalSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float RunSpeed = 1200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float MaxNoiseActionRange = 2400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float GrabDistance = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float Impulse = 5000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float FootStepCrouchNoiseRange = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float FootStepWalkNoiseRange = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float FootStepRunNoiseRange = 1200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float MinThrowDistance = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float MaxThrowDistance = 15000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	UBoxComponent* CatchBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	UPhysicsHandleComponent* PhysicsHandleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	UCameraComponent* LookCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	USceneComponent* GrabLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
    TSubclassOf<class ATwin> TwinBlueprint;
	UFUNCTION()
	void TryCatch(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent*
	              OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool bAmIOnLight = false;
	bool bAmIEnlight = false;
	void EnlightMe();
	UFUNCTION()
	void ReportTwinDeath();
	UFUNCTION(BlueprintImplementableEvent,  Category = "HideAndSeek")
    void OnCatch();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveBackwardForward(float axis);
	void MoveRightLeft(float axis);
	void Turn(float axis);
	void Lookup(float axis);
	void CrouchOn();
	void CrouchOff();
	void RunOn();
	void RunOff();
	void MakeNoise();
	void Grab();
	void Throw();
	void RemoveEnlight();
	void SummonTwin();
	bool bAmICrouch = false;
	bool bAmIRun = false;
	bool bAmIHeld = false;
	bool bHaveTwin = false;
	FTimerHandle EnlightTimerHandle;
	float HoldingTime = 0.0;
};
