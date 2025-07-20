// Fill out your copyright notice in the Description page of Project Settings.


#include "FKeyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AFKeyActor::AFKeyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh 생성 및 루트 컴포넌트로 설정
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// 트리거 박스 컴포넌트 생성 및 메시 컴포넌트에 부착
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	// 오버랩 이벤트 바인딩
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFKeyActor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFKeyActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AFKeyActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		EnableInput(PC);

		if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
		{
			if (InputAction)
			{
				EnhancedInput->BindAction(InputAction, ETriggerEvent::Started, this, &AFKeyActor::Interact);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Interaction이 할당되지 않았습니다. 에디터에서 설정해 주세요."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PC is Null"));
		}
	}
}

void AFKeyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		bCanInteract = true;
		UE_LOG(LogTemp, Warning, TEXT("플레이어가 상호작용 범이에 들어왔습니다. F 키를 눌러 주세요."));
	}
}

void AFKeyActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// 범위 밖으로 나가면 상호작용 불가능
	if (OtherActor && OtherActor != this)
	{
		bCanInteract = false;
		UE_LOG(LogTemp, Warning, TEXT("상호작용 범위를 벗어났습니다."));
	}
}

void AFKeyActor::Interact()
{
	if (bCanInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("F 키 입력 - 오브젝트를 수집했습니다!"));
	}
}

// Called every frame
void AFKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

