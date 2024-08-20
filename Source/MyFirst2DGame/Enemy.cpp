#include "Enemy.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AEnemy::OnDestroyTimerTimeout, 1.0f, false, DestroyTimerDuration);

	MovementDirection.X = 1;
	MovementDirection.Y = 0;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;
	FVector NewLocation = GetActorLocation() + FVector(DistanceToMove.X, 0.0f, DistanceToMove.Y);
	SetActorLocation(NewLocation);
}

void AEnemy::OnDestroyTimerTimeout()
{
	Destroy();
}