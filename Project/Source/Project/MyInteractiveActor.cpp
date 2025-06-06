// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractiveActor.h"

#include "Components/BoxComponent.h"


// Sets default values
AMyInteractiveActor::AMyInteractiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyInteractiveActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMyInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyInteractiveActor::OnOverlapBegin(UPrimitiveComponent* OverlapeedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player has overlapped with interactive object!"));
}

