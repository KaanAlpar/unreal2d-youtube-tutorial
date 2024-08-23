#include "MyHUD.h"

void UMyHUD::SetScore(int NewScore)
{
	// SCORE:99
	FString Str = FString::Printf(TEXT("SCORE:%d"), NewScore);
	ScoreText->SetText(FText::FromString(Str));
}