// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FKeyActor.generated.h"

// 전방 선언으로 include 최소화
class UStaticMeshComponent;
class UBoxComponent;
class UInputAction;


UCLASS()
class PROJECT_API AFKeyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFKeyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 메시 컴포넌트 생성
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// 트리거 박스
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox;

	// Enahnced Input에서 사용할 입력 액션 객체
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InputAction;

	// 플레이어가 트리거 박스에 들어왓을 때 실행되는 함수
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 플레이어가 트리거 박스를 벗어났을 때 실행되는 함수
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Interact();

	bool bCanInteract = false;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
