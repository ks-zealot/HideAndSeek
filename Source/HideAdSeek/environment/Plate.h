// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "../enemy/Enemy.h"
#include "Plate.generated.h"

/**
 * 
 */
UCLASS()
class HIDEADSEEK_API APlate : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	APlate();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	UChildActorComponent* Alarm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	TSubclassOf<class AStaticMeshActor> CubeBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	TSubclassOf<class AStaticMeshActor> PickableBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	TSubclassOf<class AEnemy> EnemyBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	int32 NumberOfCubes = 6; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	int32 NumberOfPickableCubes = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float MaxThrowNoiseRange = 2400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HideAndSeek")
	float PlateHeight = 100;
	UFUNCTION(BlueprintCallable)
    void Overlap(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
    void EndOverlap(AActor* OtherActor);
protected:
	virtual void BeginPlay() override;
private:
	float RoomHeight = 2100;
	float MinRange = -1000;
	float MaxRange = 1000;
	float CubeHeight = 110;

	bool bAmIOnLight;

	void CheckAmIOnLight();
	void SpawnEnemy();
	void SpawnPickable();
	void SpawnCubes();
	
	bool CanSpawnHere(FVector Point, FVector BoxSize);
	void MakeSpawnTry(FVector ActorSize, TSubclassOf<AActor> ActorToSpawn);
	FVector GetRandomPoint(float Height);
};
