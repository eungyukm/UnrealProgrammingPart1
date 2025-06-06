// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInteractiveActor.generated.h"

UCLASS()
class PROJECT_API AMyInteractiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyInteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapeedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
