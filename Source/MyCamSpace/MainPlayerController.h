// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MainPlayerController.generated.h"

UCLASS()
class MYCAMSPACE_API AMainPlayerController : public APlayerController
{
    GENERATED_BODY()

  public:
    AMainPlayerController();

  public:
    UFUNCTION(BlueprintCallable, Category = "InputController")
    FORCEINLINE class UInputMappingContext* GetInputContext() const;

  protected:
    virtual void BeginPlay() override;

  private:
    UPROPERTY(EditAnywhere, Category = "InputController", meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* InputContext = nullptr;

    UPROPERTY(EditAnywhere, Category = "InputController", meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction = nullptr;

    UPROPERTY(EditAnywhere, Category = "InputController", meta = (AllowPrivateAccess = "true"))
    class UInputAction* JumpAction = nullptr;

    UPROPERTY()
    class ACharacter* m_Character = nullptr;

  private:
    void Jump();
    void EndJump();
    void Move(const FInputActionValue& Value);
};

#pragma region //// Implementations ////////////////////////////////////////////////////////////////

class UInputMappingContext* AMainPlayerController::GetInputContext() const
{
    return InputContext;
}

#pragma endregion