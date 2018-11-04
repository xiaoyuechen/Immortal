// Copyright J&J.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ImmortalPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerControllerDelegate);


/**
 * This class is the player controller class for Immortal. 
 * It is Responsible for swapping characters (player's persist ability) and controlling UI.
 */

UCLASS()
class IMMORTAL_API AImmortalPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AImmortalPlayerController();
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Swap")
	void SwapCharacter();

	FPlayerControllerDelegate OnSwap;

protected:
	virtual void SetupInputComponent() override;
	virtual void QuitGame();

	void OnCharacter0Death();
	void OnOtherCharacterDeadth();


private:
	UFUNCTION()
	void OnCharacterDeath();

	/** Returns the closest pawn other than possessed pawn within the swap radius */
	APawn* GetClosestPawn();

	class ABaseCharacter* PossessedCharacter = nullptr;

	class UClass* Character0Blueprint = nullptr;

	UPROPERTY(EditAnywhere, Category = "CharacterSetup")
	float SwapRadius = 200;

};
