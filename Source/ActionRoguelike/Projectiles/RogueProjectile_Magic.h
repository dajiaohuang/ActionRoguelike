// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "GameplayTagContainer.h"
#include "RogueProjectile_Magic.generated.h"

class URogueActionEffect;

// inherit from struct in base class to expand on the Sparse properties
USTRUCT(BlueprintType)
struct FMagicProjectileSparseData : public FProjectileSparseData
{
	GENERATED_BODY()

	FMagicProjectileSparseData()
	: DamageCoefficient(100.0f)
	{}
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta=(Units="Percent"))
	float DamageCoefficient;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<URogueActionEffect> BurningActionClass;

};

UCLASS(Abstract, SparseClassDataTypes = MagicProjectileSparseData)
class ACTIONROGUELIKE_API ARogueProjectile_Magic : public ARogueProjectile
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

public:

	ARogueProjectile_Magic();

#if WITH_EDITORONLY_DATA
	//~ These properties are moving out to the FMySparseClassData struct:
	
private:
	UPROPERTY()
	float DamageCoefficient_DEPRECATED;

	UPROPERTY()
	FGameplayTag ParryTag_DEPRECATED;

	UPROPERTY()
	TSubclassOf<URogueActionEffect> BurningActionClass_DEPRECATED;
#endif
	
#if WITH_EDITOR
public:
	// ~ This function transfers existing data into FMySparseClassData.
	virtual void MoveDataToSparseClassDataStruct() const override;
#endif
};
