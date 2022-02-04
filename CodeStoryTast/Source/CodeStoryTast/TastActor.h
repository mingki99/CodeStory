// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "GenericPlatformProcess.h"

// 이 해더파일은 언리얼 전용이며 상용구가 들어있다. 밑에는 아무것도 선언하면 안된다.
#include "TastActor.generated.h"



UCLASS()
class CODESTORYTAST_API ATastActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATastActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
