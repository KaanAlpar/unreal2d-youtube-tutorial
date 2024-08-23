#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/TimerHandle.h"

#include "PlayerCharacter.h"
#include "Enemy.h"
#include "MyHUD.h"

#include "EnemySpawner.generated.h"

UCLASS()
class MYFIRST2DGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D GameAreaSize;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMyHUD> HUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMyHUD* HUDWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> EnemySprites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RestartTimerDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GameStartTimerDuration = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Score = 0;

	FTimerHandle SpawnTimer;
	FTimerHandle RestartTimer;
	FTimerHandle GameStartTimer;
	FTimerHandle ScoreTimer;

	APlayerCharacter* Player;

	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void StartSpawning();
	void StopSpawning();
	void SpawnEnemy();

	void OnSpawnTimerTimeout();
	void OnRestartTimerTimeout();
	void OnGameStartTimerTimeout();
	void OnScoreTimerTimeout();

	void SetScore(int NewScore);

	UFUNCTION()
	void OnPlayerDied();

	void StartNewGame();
};
