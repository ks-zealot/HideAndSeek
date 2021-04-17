// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Twin.generated.h"
DECLARE_DELEGATE(FKillDelegate)
UCLASS()
class HIDEADSEEK_API ATwin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwin();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HideAndSeek")
	UBoxComponent* CatchBox;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FKillDelegate KillDelegate;
	UFUNCTION(BlueprintImplementableEvent,  Category = "HideAndSeek")
    void OnDeath();
	UFUNCTION()
	void Death(UPrimitiveComponent* OverlappingComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult);
};
