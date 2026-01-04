// Copyright Simon Kramer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EurekaMathUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EUREKA_API UEurekaMathUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	// Angle Functions
	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Angle")
	static float AngleBetween(FVector2D A, FVector2D B);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Angle")
	static float SignedAngleBetween(FVector2D A, FVector2D B);

	// Segment Functions
	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Segment")
	static FVector ClosestPointOnSegment(const FVector& Point, const FVector& SegmentStart, const FVector& SegmentEnd);

	// Plane Functions
	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Plane")
	static bool GetSide(const FVector& Point, const FPlane& Plane);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Plane")
	static FVector ClosestPointOnPlane(const FVector& Point, const FPlane& Plane);

	// Triangle Functions
	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Triangle")
	static bool PointInTriangle(const FVector& Point, const FVector& TriangleP0, const FVector& TriangleP1, const FVector& TriangleP2, FVector& OutBarycentricCoords);

	UFUNCTION(BlueprintPure, Category = "Eureka|Math|Triangle")
	static bool RayTriangleIntersection(const FVector& RayOrigin, const FVector& RayDirection,
		const FVector& TriangleP0, const FVector& TriangleP1, const FVector& TriangleP2,
		FVector& OutHitPoint, FVector& OutBarycentricCoords);
};
