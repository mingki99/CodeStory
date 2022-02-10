// Fill out your copyright notice in the Description page of Project Settings.


#include "TastActor.h"

//#include "GenericPlatformProcess.h"

// Sets default values
ATastActor::ATastActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	//Tick 은 이거랑 같이 제거해주자. False 로 해놓으면 이것인 Ticking 하는것이 아니기에 CPU 싸이클을 일부 저장할수있다.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Log, TEXT("TastActor Constructor"));

}

//static void LaunchURL
//(
//	const TCHAR* URL,
//	const TCHAR* Parms,
//	FString* Error
//);

// Called when the game starts or when spawned
void ATastActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("BeginPlay"));





	//::ShellExecute(NULL, ("open"), a, NULL, NULL, SW_SHOW);

	//std::FPlatfromProcess::LaunchURL()

}

// Called every frame
void ATastActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Tick"));


}

