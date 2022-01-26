// Fill out your copyright notice in the Description page of Project Settings.


#include "Tast1.h"
#include <Windows.h>

// Sets default values
ATast1::ATast1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATast1::BeginPlay()
{
	Super::BeginPlay();
	
	const char* a = "https://www.youtube.com/";

	::ShellExecute(NULL, ("open"), a, NULL, NULL, SW_SHOW);

}

// Called every frame
void ATast1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

