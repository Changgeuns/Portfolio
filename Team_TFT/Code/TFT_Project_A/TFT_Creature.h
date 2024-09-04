// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "TFT_MeshComponent.h"
#include "TFT_StatComponent.h"
#include "TFT_InvenComponent.h"
#include "TFT_StoreComponent.h"

#include "TFT_AnimInstance_Knight.h"
#include "TFT_AnimInstance_Archer.h"

#include "TFT_Creature.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class UTFT_MeshComponent;
class UTFT_StatComponent;
class UTFT_InvenComponent;


DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);


UCLASS()
class TFT_PROJECT_A_API ATFT_Creature : public ACharacter
{
	GENERATED_BODY()

public:

	ATFT_Creature();


	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);

	int32 GetCurHp() { return _statCom->GetCurHp(); }


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetMesh(FString path) PURE_VIRTUAL(ATFT_Creature::SetMesh, );

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void AttackStart();

	UFUNCTION()
	virtual void DeathStart();

	UFUNCTION()
	virtual void Disable();

	Delegate_AttackEnded _attackEndedDelegate;


	
protected:

private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = true))
	UTFT_MeshComponent* _meshCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	UTFT_StatComponent* _statCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = true))
	UTFT_InvenComponent* _invenCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* _hpbarWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> HpBarWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;


	class UUserWidget* HpBarWidgetInstance;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Store, meta = (AllowPrivateAccess = true))
	class UTFT_StoreComponent* _storeCom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;

};
