// Fill out your copyright notice in the Description page of Project Settings.


#include "Twin.h"

#include "HideAdSeek/enemy/Enemy.h"

// Sets default values
ATwin::ATwin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CatchBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CatchBox"));
	CatchBox->SetupAttachment(GetMesh());
	
}

// Called when the game starts or when spawned
void ATwin::BeginPlay()
{
	Super::BeginPlay();
	CatchBox->OnComponentBeginOverlap.AddDynamic(this, &ATwin::Death);
}

// Called every frame
void ATwin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATwin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATwin::Death(UPrimitiveComponent* OverlappingComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		OnDeath();
		KillDelegate.ExecuteIfBound();
	}
}
