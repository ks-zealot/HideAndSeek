// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/AudioComponent.h"
#include "HideAdSeek/player/PlayableCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LeftEye1 = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftEye1"));
	RightEye1 = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightEye1"));
	LeftEye1->SetupAttachment(GetMesh());
	RightEye1->SetupAttachment(GetMesh());
	LeftEye2 = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftEye2"));
	RightEye2 = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightEye2"));
	LeftEye2->SetupAttachment(GetMesh());
	RightEye2->SetupAttachment(GetMesh());
	Sight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sight"));
	Hearing = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Hearing"));
	Sight->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy::HandleSight);
	Hearing->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy::HandleHearing);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	Reset();
}


void AEnemy::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
	FActorPerceptionBlueprintInfo Info;
	Sight->GetActorsPerception(Actor, Info);
	for (FAIStimulus Stimul  : Info.LastSensedStimuli)
	{
		if (Stimul.WasSuccessfullySensed())
		{
			
			AEnemy* Enemy = Cast<AEnemy>(Actor);
			if (Enemy)
			{
				return;
			}
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsBool(FName("CanSensePlayer"), true);
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsVector(
                FName("SenseLocation"), Actor->GetActorLocation());
			SetEyes(SightIntensity, SightRadius, SightInnerConeAngle);
			GetCharacterMovement()->MaxWalkSpeed = SightSpeed;
		}
	}
}

void AEnemy::HandleHearing(AActor* Actor, FAIStimulus Stimulus)
{
	FActorPerceptionBlueprintInfo Info;
	Hearing->GetActorsPerception(Actor, Info);
	for (FAIStimulus Stimul : Info.LastSensedStimuli)
	{
		if (Stimul.WasSuccessfullySensed())
		{
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsBool(FName("CanSensePlayer"), true);
			UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsVector(
				FName("SenseLocation"), Stimul.StimulusLocation);
			SetEyes(HearingIntensity, HearingRadius, HearingInnerConeAngle);
			GetCharacterMovement()->MaxWalkSpeed = HearingIntensity;
			PlayStomp();
		}
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetEyes(float Intentcity, float Radius,float InnerConeAngle)
{
	LeftEye1->SetIntensity(Intentcity);
	RightEye1->SetIntensity(Intentcity);
	LeftEye1->SetAttenuationRadius(Radius);
	RightEye1->SetAttenuationRadius(Radius);
	LeftEye2->SetIntensity(Intentcity);
	RightEye2->SetIntensity(Intentcity);
	LeftEye2->SetAttenuationRadius(Radius);
	RightEye2->SetAttenuationRadius(Radius);
	LeftEye2->SetInnerConeAngle(InnerConeAngle);
	RightEye2->SetInnerConeAngle(InnerConeAngle);
	LeftEye2->SetInnerConeAngle(InnerConeAngle);
	RightEye2->SetInnerConeAngle(InnerConeAngle);
}

void AEnemy::PlayStomp()
{
	AudioComponent->Activate();
	if (!AudioComponent->IsPlaying())
	{
		AudioComponent->Play();
	}
}

void AEnemy::Reset()
{
	SetEyes(DefaultIntensity, DefaultRadius, DefaultInnerConeAngle);
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}
