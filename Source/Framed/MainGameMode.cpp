// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"

#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "Utils.hpp"

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld()) {
        auto cameras = FramedUtils::FindAllActors<ACameraActor>(World);
        auto* controller = World->GetFirstPlayerController();

        if (cameras.Num() > 0)
            controller->SetViewTarget(cameras[0]);
    }
}
