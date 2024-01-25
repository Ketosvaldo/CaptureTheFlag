// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CaptureTheFlagCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ACaptureTheFlagCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Fire action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SelectWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ACaptureTheFlagProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGrenade> GrenadeClass;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABoomerang> BoomerangClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh, meta=(AllowPrivateAccess = "true"))
	UArrowComponent* ProjectileDirection;
	
public:
	ACaptureTheFlagCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Values)
	bool bHasFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values)
	bool bIsBlue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values)
	bool bIsDeath;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values)
	bool bIsRagdoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values)
	int Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values)
	int GrenadeNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values, Replicated)
	bool bHaveBoomerang;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values, Replicated)
	bool bIsGrenade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Values, Replicated)
	bool bIsBoomerang;

protected:
	virtual void BeginPlay();

	void Tick(float DeltaSeconds) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;
	
	void Fire();
	
	UFUNCTION(Server,Reliable)
	void Fire_OnServer();

	bool CanShoot();

	UFUNCTION(Server, Reliable)
	void SetIsGrenade();

	UFUNCTION(Server, Reliable)
	void UnsetIsGrenade();

	UFUNCTION(Server, Reliable)
	void SetIsBoomerang(bool bState);

	UFUNCTION(Server, Reliable)
	void SetHaveBoomerang(bool state);
	
	void SelectWeapon(const FInputActionValue& Value);

	float shoot;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	UFUNCTION(BlueprintCallable)
	void JoinGameSession();

	//Callbacks
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccess);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	IOnlineSessionPtr OnlineSessionInterface;

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};

