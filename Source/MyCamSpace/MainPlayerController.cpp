// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"

#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMainPlayerController::AMainPlayerController()
{
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultContext(
        TEXT("/Game/Defaults/Input/IMC_Main"));

    if (DefaultContext.Succeeded()) {
        InputContext = DefaultContext.Object;
        check(InputContext != nullptr)
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> DefaultMove(
        TEXT("/Game/Defaults/Input/IA_Move"));

    if (DefaultContext.Succeeded()) {
        MoveAction = DefaultMove.Object;
        check(MoveAction != nullptr)
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> DefaultJump(
        TEXT("/Game/Defaults/Input/IA_Jump"));

    if (DefaultContext.Succeeded()) {
        JumpAction = DefaultJump.Object;
        check(JumpAction != nullptr)
    }
}

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Setup Input Context
    if (auto* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {

        if (!InputContext)
            return;

        Subsystem->AddMappingContext(InputContext, 0);
    }

    // Bind Inputs Actions
    auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    m_Character = GetCharacter();

    if (MoveAction) {
        EnhancedInputComponent->BindAction(
            MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
    }

    if (JumpAction) {
        EnhancedInputComponent->BindAction(
            JumpAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Jump);

        EnhancedInputComponent->BindAction(
            JumpAction, ETriggerEvent::Completed, this, &AMainPlayerController::EndJump);
    }
}

void AMainPlayerController::Jump()
{
    if (!m_Character)
        return;

    m_Character->Jump();
}

void AMainPlayerController::EndJump()
{
    if (!m_Character)
        return;

    m_Character->StopJumping();
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
    if (!m_Character)
        return;

    auto scale = Value.Get<FInputActionValue::Axis1D>();

    m_Character->AddMovementInput(FVector(0.5, 0.0, 0.0), scale);

    if (scale > 0.f) {
        SetControlRotation(FRotator(0.0, 0.0, 0.0));

    } else if (scale < 0.f) {
        SetControlRotation(FRotator(0.0, 180.0, 0.0));
    }
}
