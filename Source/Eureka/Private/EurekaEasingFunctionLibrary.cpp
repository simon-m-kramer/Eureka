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
    const float Period = 0.5f;
    return FMath::Pow(2.0f, -10.0f * f) * FMath::Sin((f - Period / 4.0f) * (2.0f * PI) / Period) + 1.0f;
}

float UEurekaEasingFunctionLibrary::OutBounce(float f)
{
    const float Divisor = 2.75f;
    const float Multiplier = 7.5625f;

    if (f < 1.0f / Divisor)
    {
        return Multiplier * f * f;
    }
    else if (f < 2.0f / Divisor)
    {
        f -= 1.5f / Divisor;
        return Multiplier * f * f + 0.75f;
    }
    else if (f < 2.5f / Divisor)
    {
        f -= 2.25f / Divisor;
        return Multiplier * f * f + 0.9375f;
    }
    else
    {
        f -= 2.625f / Divisor;
        return Multiplier * f * f + 0.984375f;
    }
}
