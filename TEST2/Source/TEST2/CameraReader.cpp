// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraReader.h"

// Sets default values
ACameraReader::ACameraReader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>("Root");
	Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen_Raw");
	Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen_Post");

	Brightness = 0;
	Multiply = 1;

	//Initialize OpenCV and webcam properties
	CameraID = 0;
	VideoTrackID = 0;
	isStreamOpen = false;
	VideoSize = FVector2D(1920, 1080);
	RefreshRate = 30.0f;
}

// Called when the game starts or when spawned
void ACameraReader::BeginPlay()
{
	Super::BeginPlay();
	isStreamOpen = true;
	//Prepare the color data array
	ColorData.AddDefaulted(VideoSize.X * VideoSize.Y);
	//setup openCV
	cvSize = cv::Size(VideoSize.X, VideoSize.Y);
	cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());
	//create dynamic texture
	Camera_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);


#if WITH_EDITORONLY_DATA
	Camera_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
	Camera_Texture2D->SRGB = Camera_RenderTarget->SRGB;
}

// Called every frame
void ACameraReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshTimer += DeltaTime;
	if (isStreamOpen && RefreshTimer >= 1.0f / RefreshRate)
	{
		RefreshTimer -= 1.0f / RefreshRate;
		ReadFrame();
		OnNextVideoFrame();
	}
}

bool ACameraReader::ReadFrame() {
	if (!Camera_Texture2D || !Camera_RenderTarget) return false;
	//Read the pixels from the RenderTarget and store them in a FColor array
	//TArray<FColor> SurfData;
	FRenderTarget* RenderTarget = Camera_RenderTarget->GameThread_GetRenderTargetResource();
	RenderTarget->ReadPixels(ColorData);
	//Get the color data
	cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());

	cvMat.convertTo(cvMat, -1, Multiply, Brightness);

	//show the openCV window
	if (!cvMat.empty())
		cv::imshow("Display", cvMat);

	//Lock the texture so we can read / write to it
	void* TextureData = Camera_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	const int32 TextureDataSize = ColorData.Num() * 4;
	//set the texture data
	FMemory::Memcpy(TextureData, ColorData.GetData(), TextureDataSize);
	//unlock the texture
	Camera_Texture2D->PlatformData->Mips[0].BulkData.Unlock();
	//Apply Texture changes to GPU memory
	Camera_Texture2D->UpdateResource();

	return true;
}
