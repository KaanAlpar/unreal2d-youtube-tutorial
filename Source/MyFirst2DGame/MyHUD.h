#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRST2DGAME_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	void SetScore(int NewScore);
};
