#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the game area size from the camera
	AActor* CameraSearch = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	if (CameraSearch)
	{
		ACameraActor* CA = Cast<ACameraActor>(CameraSearch);
		UCameraComponent* CU = CA->GetCameraComponent();

		GameAreaSize.X = CU->OrthoWidth;
		GameAreaSize.Y = CU->OrthoWidth / CU->AspectRatio;

		UE_LOG(LogTemp, Display, TEXT("%f, %f"), GameAreaSize.X, GameAreaSize.Y);
	}

	// Give the player the limits
	AActor* PlayerSearch = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (PlayerSearch)
	{
		Player = Cast<APlayerCharacter>(PlayerSearch);

		Player->HorizontalLimits.X = -GameAreaSize.X / 2.0f;
		Player->HorizontalLimits.Y = GameAreaSize.X / 2.0f;

		Player->VerticalLimits.X = -GameAreaSize.Y / 2.0f;
		Player->VerticalLimits.Y = GameAreaSize.Y / 2.0f;

		Player->PlayerDiedDelegate.AddDynamic(this, &AEnemySpawner::OnPlayerDied);
	}

	StartNewGame();
}

void AEnemySpawner::StartNewGame()
{
	// Destroy all the current enemies
	TArray<AActor*> EnemySearchArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), EnemySearchArray);
	if (EnemySearchArray.Num() > 0)
	{
		for (AActor* EnemyActor : EnemySearchArray)
		{
			AEnemy* Enemy = Cast<AEnemy>(EnemyActor);
			if (Enemy)
			{
				Enemy->Destroy();
			}
		}
	}

	// Reset the player
	if (Player)
	{
		Player->IsAlive = true;
		Player->SpriteComp->SetVisibility(true);
		Player->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Reset the score


	// Start spawning enemies again
	GetWorldTimerManager().SetTimer(GameStartTimer, this, &AEnemySpawner::OnGameStartTimerTimeout, 1.0f, false, GameStartTimerDuration);
}

void AEnemySpawner::OnGameStartTimerTimeout()
{
	StartSpawning();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::StartSpawning()
{
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::OnSpawnTimerTimeout, SpawnTime, true, SpawnTime);
}

void AEnemySpawner::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void AEnemySpawner::OnSpawnTimerTimeout()
{
	SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	// Calculate a random spawn position for the enemy
	FVector2D SpawnPos = { 0.0f, 0.0f };

	float SpawnChance = FMath::FRand();
	if (SpawnChance < 0.5f)
	{
		SpawnPos.X = GameAreaSize.X / 2.0f;
		if (SpawnChance < 0.25f)
		{
			SpawnPos.X *= -1.0f;
		}

		SpawnPos.Y = FMath::FRandRange(-GameAreaSize.Y / 2.0f, GameAreaSize.Y / 2.0f);
	}
	else
	{
		SpawnPos.Y = GameAreaSize.Y / 2.0f;
		if (SpawnChance < 0.75f)
		{
			SpawnPos.Y *= -1.0f;
		}

		SpawnPos.X = FMath::FRandRange(-GameAreaSize.X / 2.0f, GameAreaSize.X / 2.0f);
	}

	// Calculate the movement direction for the enemy
	FVector2D MovementDirection = { 0.0f, 0.0f };

	FVector2D CenterPos = { 0.0f, 0.0f };
	MovementDirection = CenterPos - SpawnPos;

	FVector PlayerPos = Player->GetActorLocation();
	MovementDirection = FVector2D(PlayerPos.X, PlayerPos.Z) - SpawnPos;

	MovementDirection.Normalize();

	// Spawn the enemy and set it up
	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyActorToSpawn, FVector(SpawnPos.X, 0.0f, SpawnPos.Y), FRotator::ZeroRotator);
	if (Enemy)
	{
		Enemy->MovementDirection = MovementDirection;

		int RandomIndex = FMath::RandRange(0, EnemySprites.Num() - 1);
		Enemy->SpriteComp->SetSprite(EnemySprites[RandomIndex]);
	}
}

void AEnemySpawner::OnPlayerDied()
{
	StopSpawning();

	GetWorldTimerManager().SetTimer(RestartTimer, this, &AEnemySpawner::OnRestartTimerTimeout, 1.0f, false, RestartTimerDuration);
}

void AEnemySpawner::OnRestartTimerTimeout()
{
	StartNewGame();
}