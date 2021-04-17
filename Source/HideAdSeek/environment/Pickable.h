// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

UCLASS()
class HIDEADSEEK_API APickable : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();
	UPROPERTY(BlueprintReadWrite)
	bool bAmITaken = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
