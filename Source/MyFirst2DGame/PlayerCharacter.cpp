#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add the mapping context
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// Bind actions to functions
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveTrigger);
		EIC->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveCompleted);
	}
}

void APlayerCharacter::MoveTrigger(const FInputActionValue& Value)
{

}

void APlayerCharacter::MoveCompleted(const FInputActionValue& Value)
{

}