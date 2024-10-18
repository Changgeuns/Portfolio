// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Creature.h"
#include "EnhancedInput/Public/InputAction.h"
#include "TFT_StatComponent.h"
#include "TFT_InteractionInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

#include "TFT_AnimInstance_Knight.h"
#include "TFT_AnimInstance_Archer.h"
#include "TFT_AnimInstance_TestMannequin.h"

#include "TFT_AnimInstance_IY.h"
#include "TFT_AnimInstance_CG.h"
#include "TFT_AnimInstance_BJ.h"
#include "TFT_AnimInstance_DH.h"

#include "TFT_Player.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UBoxComponent;


UCLASS()
class TFT_PROJECT_A_API ATFT_Player : public ATFT_Creature, public ITFT_InteractionInterface
{
	GENERATED_BODY()
public:
	ATFT_Player();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Init();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact(ATFT_Item* item) override;

	UFUNCTION()
	void LevelUp();

protected:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void JumpA(const FInputActionValue& value);
	virtual void AttackA(const FInputActionValue& value);
	void InvenopenA(const FInputActionValue& value);
	void EquipmentA(const FInputActionValue& value);
	void UseSkill(const FInputActionValue& value);
	void Rolling();	

	virtual void PlayE_Skill(const FInputActionValue& value) {};
	virtual void PlayQ_Skill(const FInputActionValue& value) {};
	virtual void PlayAttack(const FInputActionValue& value) {};
	virtual void Dash(const FInputActionValue& value) {};
	virtual void DoubleTapDash_Front(const FInputActionValue& value) {};
	virtual void DoubleTapDash_Back(const FInputActionValue& value) {};
	virtual void DoubleTapDash_Left(const FInputActionValue& value) {};
	virtual void DoubleTapDash_Right(const FInputActionValue& value) {};
	virtual void StartSprint();
	virtual void StopSprint();
	
public:
	void AddItemPlayer(ATFT_Item* item);
	void AddItemHendle(ATFT_Item* item, int32 index);
	void DropItemPlayer(ATFT_Item* item, int32 index);
	void SellItemPlayer(ATFT_Item* item, int32 index);
	void UseItemPlayer(ATFT_Item* item, int32 index);
	void UseItemPlayer_Equipment(ATFT_Item* item);
	void UIGold(int32 gold);
	void ChangeEquipment(ATFT_Item* item);
	void CloseResetEquipment();

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetPartyUI();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AlllowPrivateAccess = "true"))
	UInputAction* _dashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AlllowPrivateAccess = "true"))
	bool _canMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AlllowPrivateAccess = "true"))
	UInputAction* _doubleTapDash_W_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AlllowPrivateAccess = "true"))
	UInputAction* _doubleTapDash_A_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AlllowPrivateAccess = "true"))
	UInputAction* _doubleTapDash_S_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AlllowPrivateAccess = "true"))
	UInputAction* _doubleTapDash_D_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _invenOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _EquipmentAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _skillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _interactAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _playESkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _playQSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _playAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* _rollingAction;

	class ITFT_InteractionInterface* _interface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _attackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_Knight* _animInstanceKnight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_Archer* _animInstanceArcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_TestMannequin* _animInstanceTM;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_IY* _animInstanceIY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_DH* _animInstanceDH;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_CG* _animInstanceCG;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	class UTFT_AnimInstance_BJ* _animInstanceBJ;

	UPROPERTY(EditAnywhere)
	UAnimMontage* _rollingMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _myAnimMontage;

	


protected:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bCanDash = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bBlockInputOnDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float dashStrength_Ground = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float dashStrength_Air = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta =(UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float dashEndDempener;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UBoxComponent* _triggerBox;

};