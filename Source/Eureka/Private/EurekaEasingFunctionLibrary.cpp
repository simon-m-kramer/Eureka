// Copyright Simon Kramer. All Rights Reserved.


#include "EurekaEasingFunctionLibrary.h"



float UEurekaEasingFunctionLibrary::Linear(float f)
{
    return f;
}

float UEurekaEasingFunctionLibrary::EaseIn(float f)
{
    return f * f;
}

float UEurekaEasingFunctionLibrary::EaseOut(float f)
{
    return 1.0f - EaseIn(1.0f - f);
}

float UEurekaEasingFunctionLibrary::SmoothStep(float f)
{
    return f * f * (3.0f - 2.0f * f);
}

float UEurekaEasingFunctionLibrary::EaseOutElastic(float f)
{
	float p = 0.5f;
	return FMath::Pow(2, -10 * f) * FMath::Sin((f - p / 4) * (2 * PI) / p) + 1;
}

float UEurekaEasingFunctionLibrary::OutBounce(float f)
{
    float div = 2.75f;
    float mult = 7.5625f;

    if (f < 1 / div)
    {
        return mult * f * f;
    }
    else if (f < 2 / div)
    {
        f -= 1.5f / div;
        return mult * f * f + 0.75f;
    }
    else if (f < 2.5 / div)
    {
        f -= 2.25f / div;
        return mult * f * f + 0.9375f;
    }
    else
    {
        f -= 2.625f / div;
        return mult * f * f + 0.984375f;
    }
}
