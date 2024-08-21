#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/TimerHandle.h"

#include "PlayerCharacter.h"
#include "Enemy.h"

#include "EnemySpawner.generated.h"

UCLASS()
class MYFIRST2DGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D GameAreaSize;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> EnemySprites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 3.0f;

	FTimerHandle SpawnTimer;

	APlayerCharacter* Player;

	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void StartSpawning();
	void StopSpawning();
	void SpawnEnemy();

	void OnSpawnTimerTimeout();
};
