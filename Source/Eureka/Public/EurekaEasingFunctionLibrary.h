// Copyright Simon Kramer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EurekaEasingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EUREKA_API UEurekaEasingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float Linear(float f);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float EaseIn(float f);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float EaseOut(float f);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float SmoothStep(float f);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float EaseOutElastic(float f);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Easing")
	static float OutBounce(float f);



};
