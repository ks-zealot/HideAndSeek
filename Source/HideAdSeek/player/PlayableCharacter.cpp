// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"


#include "DrawDebugHelpers.h"
#include "HideAdSeek/enemy/Enemy.h"
#include "HideAdSeek/environment/Pickable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CatchBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CatchBox"));
	CatchBox->SetupAttachment(GetMesh());
	LookCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LookCamera"));
	LookCamera->SetupAttachment(GetMesh());
	GrabLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GrabLocation"));
	GrabLocation->SetupAttachment(GetMesh());
	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandler"));
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	CatchBox->OnComponentBeginOverlap.AddDynamic(this, &APlayableCharacter::TryCatch);
	if (InputComponent)
	{
		InputComponent->BindAxis
		(
			"MoveBackwardForward",
			this, // The object instance that is going to react to the input
			&APlayableCharacter::MoveBackwardForward // The function that will fire when input is received
		);
		InputComponent->BindAxis
		(
			"MoveRightLeft",
			this, // The object instance that is going to react to the input
			&APlayableCharacter::MoveRightLeft // The function that will fire when input is received
		);
		InputComponent->BindAxis
		(
			"Turn",
			this, // The object instance that is going to react to the input
			&APlayableCharacter::Turn // The function that will fire when input is received
		);
		InputComponent->BindAxis
		(
			"Lookup",
			this, // The object instance that is going to react to the input
			&APlayableCharacter::Lookup // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Crouch",
			IE_Pressed,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::CrouchOn // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Crouch",
			IE_Released,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::CrouchOff // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Run",
			IE_Pressed,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::RunOn // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Run",
			IE_Released,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::RunOff // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"MakeNoise",
			IE_Released,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::MakeNoise // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"SummonTwin",
			IE_Released,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::SummonTwin // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Grab",
			IE_Pressed,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::Grab // The function that will fire when input is received
		);
		InputComponent->BindAction
		(
			"Grab",
			IE_Released,
			this, // The object instance that is going to react to the input
			&APlayableCharacter::Throw // The function that will fire when input is received
		);
	}
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bAmIHeld)
	{
		PhysicsHandleComponent->SetTargetLocation(GrabLocation->GetComponentLocation());
		if (HoldingTime < 1)
		{
			HoldingTime  = HoldingTime + DeltaTime / 2;
		}
	}
	if (!UKismetMathLibrary::Vector_IsNearlyZero(GetCharacterMovement()->GetLastUpdateVelocity(), 0.01))
	{
		if (bAmICrouch)
		{
			UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this, FootStepCrouchNoiseRange, FName());
		}
		else if (bAmIRun)
		{
			UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this, FootStepRunNoiseRange, FName());
		}
		else
		{
			UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this, FootStepWalkNoiseRange, FName());
		}
	}
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayableCharacter::MoveBackwardForward(float axis)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axis);
}

void APlayableCharacter::MoveRightLeft(float axis)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, axis);
}

void APlayableCharacter::Turn(float axis)
{
	AddControllerYawInput(axis);
}

void APlayableCharacter::Lookup(float axis)
{
	AddControllerPitchInput(axis);
}

void APlayableCharacter::CrouchOn()
{
	bAmIRun = false;
	bAmICrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void APlayableCharacter::CrouchOff()
{
	bAmICrouch = false;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void APlayableCharacter::RunOn()
{
	bAmIRun = true;
	bAmICrouch = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayableCharacter::RunOff()
{
	bAmIRun = false;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void APlayableCharacter::TryCatch(UPrimitiveComponent* OverlappingComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (Cast<AEnemy>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Catched"))
		OnCatch();
	}
}

void APlayableCharacter::MakeNoise()
{
	UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), 1.0, this, MaxNoiseActionRange, FName());
}

void APlayableCharacter::Grab()
{
	FVector Start = LookCamera->GetComponentLocation();
	FVector End = LookCamera->GetComponentLocation() + LookCamera->GetForwardVector() * GrabDistance;
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel3))
	{
		APickable* Pickable = Cast<APickable>(HitResult.Actor);

		if (Pickable)
		{
			PhysicsHandleComponent->GrabComponentAtLocation(HitResult.GetComponent(), HitResult.BoneName,
			                                                HitResult.Location);
			bAmIHeld = true;
			Pickable->bAmITaken = true;
		}
	}
}

void APlayableCharacter::Throw()
{
	if (bAmIHeld)
	{
		bAmIHeld = false;
		PhysicsHandleComponent->GetGrabbedComponent()->AddImpulse(LookCamera->GetForwardVector() *
			FMath::Lerp(MinThrowDistance, MaxThrowDistance, HoldingTime),
		                                                          FName(), true);
		PhysicsHandleComponent->ReleaseComponent();
	}
}


void APlayableCharacter::EnlightMe()
{
	if (!bAmIEnlight)
	{
		bAmIEnlight = true;
		GetWorld()->GetTimerManager().SetTimer(EnlightTimerHandle, this, &APlayableCharacter::RemoveEnlight, 0.4,
		                                       false);
	}
}

void APlayableCharacter::RemoveEnlight()
{
	bAmIEnlight = false;
}

void APlayableCharacter::SummonTwin()
{
	if (bHaveTwin)
	{
		return;
	}
	FVector Location = GetActorLocation() + GetActorForwardVector() * 600;
	Location.Z = 200.0;
	FHitResult HitResult;
	bool bCanSpawn = !UKismetSystemLibrary::BoxTraceSingle(this, Location, Location,
	                                                       FVector(100, 100, 100), FRotator::ZeroRotator,
	                                                       UEngineTypes::ConvertToTraceType(ECC_Visibility),
	                                                       false, TArray<AActor*>(), EDrawDebugTrace::None,
	                                                       HitResult, true,
	                                                       FLinearColor::Green, FLinearColor::Red, 0.0f);
	if (bCanSpawn)
	{
		FTransform Transform = UKismetMathLibrary::MakeTransform(Location, FRotator::ZeroRotator,
		                                                         FVector::OneVector);
		ATwin* Twin = GetWorld()->SpawnActor<ATwin>(TwinBlueprint, Transform);
		Twin->KillDelegate.BindUObject(this, &APlayableCharacter::ReportTwinDeath);
		bHaveTwin = true;
	}
}

void APlayableCharacter::ReportTwinDeath()
{
	bHaveTwin = false;
}
