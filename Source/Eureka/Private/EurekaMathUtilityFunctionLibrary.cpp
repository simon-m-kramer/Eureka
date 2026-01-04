// Copyright Simon Kramer. All Rights Reserved.


#include "EurekaMathUtilityFunctionLibrary.h"

float UEurekaMathUtilityFunctionLibrary::AngleBetween(FVector2D A, FVector2D B)
{
	const float Dot = FVector2D::DotProduct(A, B);
	const float Magnitudes = A.Size() * B.Size();

	if (Magnitudes < KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	const float CosAngle = FMath::Clamp(Dot / Magnitudes, -1.0f, 1.0f);
	return FMath::RadiansToDegrees(FMath::Acos(CosAngle));
}

float UEurekaMathUtilityFunctionLibrary::SignedAngleBetween(FVector2D A, FVector2D B)
{
	const FVector2D Right(A.Y, -A.X);
	const float Dot = FVector2D::DotProduct(A, B);
	const float Magnitudes = A.Size() * B.Size();

	if (Magnitudes < KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	const float CosAngle = FMath::Clamp(Dot / Magnitudes, -1.0f, 1.0f);
	const float Sign = FMath::Sign(FVector2D::DotProduct(B, Right));

	return FMath::RadiansToDegrees(FMath::Acos(CosAngle)) * Sign;
}

FVector UEurekaMathUtilityFunctionLibrary::ClosestPointOnSegment(const FVector& Point, const FVector& SegmentStart, const FVector& SegmentEnd)
{
	const FVector Segment = SegmentEnd - SegmentStart;
	const FVector StartToPoint = Point - SegmentStart;

	const float SegmentLengthSquared = Segment.SizeSquared();

	// Degenerate segment case
	if (SegmentLengthSquared < KINDA_SMALL_NUMBER)
	{
		return SegmentStart;
	}

	// Project point onto segment
	const float T = FMath::Clamp(FVector::DotProduct(StartToPoint, Segment) / SegmentLengthSquared, 0.0f, 1.0f);

	return SegmentStart + Segment * T;
}

bool UEurekaMathUtilityFunctionLibrary::GetSide(const FVector& Point, const FPlane& Plane)
{
	return Plane.PlaneDot(Point) >= 0.0f;
}

FVector UEurekaMathUtilityFunctionLibrary::ClosestPointOnPlane(const FVector& Point, const FPlane& Plane)
{
	const float Distance = Plane.PlaneDot(Point);
	return Point - (FVector(Plane) * Distance);
}

bool UEurekaMathUtilityFunctionLibrary::PointInTriangle(const FVector& Point, const FVector& TriangleP0, const FVector& TriangleP1, const FVector& TriangleP2, FVector& OutBarycentricCoords)
{
	// Compute vectors
	const FVector V0 = TriangleP2 - TriangleP0;
	const FVector V1 = TriangleP1 - TriangleP0;
	const FVector V2 = Point - TriangleP0;

	// Compute dot products
	const float Dot00 = FVector::DotProduct(V0, V0);
	const float Dot01 = FVector::DotProduct(V0, V1);
	const float Dot02 = FVector::DotProduct(V0, V2);
	const float Dot11 = FVector::DotProduct(V1, V1);
	const float Dot12 = FVector::DotProduct(V1, V2);

	// Compute barycentric coordinates
	const float Denominator = Dot00 * Dot11 - Dot01 * Dot01;

	if (FMath::Abs(Denominator) < KINDA_SMALL_NUMBER)
	{
		OutBarycentricCoords = FVector::ZeroVector;
		return false;
	}

	const float InvDenom = 1.0f / Denominator;
	const float U = (Dot11 * Dot02 - Dot01 * Dot12) * InvDenom;
	const float V = (Dot00 * Dot12 - Dot01 * Dot02) * InvDenom;
	const float W = 1.0f - (U + V);

	OutBarycentricCoords = FVector(W, V, U);

	// Check if point is in triangle
	return (U >= 0.0f) && (V >= 0.0f) && (U + V <= 1.0f);
}

bool UEurekaMathUtilityFunctionLibrary::RayTriangleIntersection(const FVector& RayOrigin, const FVector& RayDirection,
	const FVector& TriangleP0, const FVector& TriangleP1, const FVector& TriangleP2,
	FVector& OutHitPoint, FVector& OutBarycentricCoords)
{
	OutHitPoint = FVector::ZeroVector;
	OutBarycentricCoords = FVector::ZeroVector;

	// Calculate plane from triangle
	const FVector Edge1 = TriangleP1 - TriangleP0;
	const FVector Edge2 = TriangleP2 - TriangleP0;
	const FVector Normal = FVector::CrossProduct(Edge1, Edge2).GetSafeNormal();

	// Check if ray is parallel to triangle
	const float NDotRayDir = FVector::DotProduct(Normal, RayDirection);
	if (FMath::Abs(NDotRayDir) < KINDA_SMALL_NUMBER)
	{
		return false; // Ray is parallel to triangle
	}

	// Compute distance from ray origin to plane
	const float D = -FVector::DotProduct(Normal, TriangleP0);
	const float T = -(FVector::DotProduct(Normal, RayOrigin) + D) / NDotRayDir;

	// Check if intersection is behind ray origin
	if (T < 0.0f)
	{
		return false;
	}

	// Calculate point on plane
	const FVector PointOnPlane = RayOrigin + RayDirection * T;

	// Check if point is inside triangle
	if (PointInTriangle(PointOnPlane, TriangleP0, TriangleP1, TriangleP2, OutBarycentricCoords))
	{
		OutHitPoint = PointOnPlane;
		return true;
	}

	return false;
}


