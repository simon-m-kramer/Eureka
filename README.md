# Eureka Math Utilities

A collection of mathematical utility functions for Unreal Engine, providing easing functions, geometric calculations, and common math operations for game development. Based on math utilities by Carl Granberg, converted from Unity/C# to Unreal Engine/C++.

## Features

### 🎨 Easing Functions
- **Linear** - No easing
- **EaseIn** - Quadratic ease in (acceleration)
- **EaseOut** - Quadratic ease out (deceleration)
- **SmoothStep** - Smooth Hermite interpolation
- **EaseOutElastic** - Elastic bounce effect
- **OutBounce** - Bouncing deceleration

### 📐 Geometric Utilities
- **Angle Calculations** - Calculate angles between 2D vectors (signed and unsigned)
- **Segment Operations** - Find closest points on line segments
- **Plane Operations** - Point-to-plane projections and side testing
- **Triangle Operations** - Point-in-triangle tests and ray-triangle intersections with barycentric coordinates

## Installation

1. Download or clone this repository
2. Copy the `Eureka` folder to your project's `Plugins` directory
3. Add the plugin to your project's `.uproject` file (if not already auto-detected):
```json
"Plugins": [
    {
        "Name": "Eureka",
        "Enabled": true
    }
]
```
4. Add the plugin module to your project's `Build.cs` file:
```csharp
PublicDependencyModuleNames.AddRange(new string[] { 
    "Core", 
    "CoreUObject", 
    "Engine",
    "Eureka"  // Add this line
});
```
5. Restart Unreal Engine and regenerate project files
6. The plugin should now appear in Edit → Plugins → Project → Eureka

## Usage Examples

### 🎨 Easing Functions

#### C++ Example
```cpp
#include "EurekaEasingFunctionLibrary.h"

// Smooth animation over time
float AnimationProgress = GetWorld()->GetTimeSeconds() - StartTime;
float NormalizedTime = FMath::Clamp(AnimationProgress / Duration, 0.0f, 1.0f);
float EasedValue = UEurekaEasingFunctionLibrary::SmoothStep(NormalizedTime);

// Apply to position
FVector CurrentPosition = FMath::Lerp(StartPosition, EndPosition, EasedValue);
```

#### Common Use Cases
```cpp
// Smooth camera movement
float T = UEurekaEasingFunctionLibrary::EaseOut(Alpha);
Camera->SetWorldLocation(FMath::Lerp(StartLoc, EndLoc, T));

// Bounce landing effect
float BounceT = UEurekaEasingFunctionLibrary::OutBounce(LandingProgress);
Character->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f - BounceT * 0.2f));

// Elastic UI popup
float ElasticT = UEurekaEasingFunctionLibrary::EaseOutElastic(PopupProgress);
Widget->SetRenderScale(FVector2D(ElasticT));
```

### 📐 Angle Calculations

#### C++ Example
```cpp
#include "EurekaMathUtilityFunctionLibrary.h"

// Calculate unsigned angle between two directions
FVector2D DirectionA = FVector2D(1, 0);
FVector2D DirectionB = FVector2D(0, 1);
float Angle = UEurekaMathUtilityFunctionLibrary::AngleBetween(DirectionA, DirectionB);
// Returns: 90.0

// Calculate signed angle (useful for steering)
FVector2D Forward = PlayerForward.ToVector2D();
FVector2D ToTarget = (TargetLocation - PlayerLocation).ToVector2D();
float SteeringAngle = UEurekaMathUtilityFunctionLibrary::SignedAngleBetween(Forward, ToTarget);
// Returns: -45.0 to 45.0 (negative = turn left, positive = turn right)
```

### 📏 Closest Point on Segment

#### C++ Example
```cpp
// Find nearest point on a path segment
FVector PlayerPos = GetActorLocation();
FVector PathStart = Waypoint1->GetActorLocation();
FVector PathEnd = Waypoint2->GetActorLocation();

FVector ClosestPoint = UEurekaMathUtilityFunctionLibrary::ClosestPointOnSegment(
    PlayerPos, PathStart, PathEnd
);

// Use for path following
FVector DirectionToPath = (ClosestPoint - PlayerPos).GetSafeNormal();
AddMovementInput(DirectionToPath);
```

### ✈️ Plane Operations

#### C++ Example
```cpp
// Create a ground plane
FPlane GroundPlane(FVector::UpVector, 0.0f);

// Check which side of plane a point is on
FVector ProjectileLocation = Projectile->GetActorLocation();
bool bAboveGround = UEurekaMathUtilityFunctionLibrary::GetSide(ProjectileLocation, GroundPlane);

// Project point onto plane
FVector GroundPosition = UEurekaMathUtilityFunctionLibrary::ClosestPointOnPlane(
    ProjectileLocation, GroundPlane
);
```

### 🔺 Triangle Operations

#### Point in Triangle
```cpp
// Check if click is inside a triangle (useful for custom UI or selection)
FVector ClickPosition = HitResult.Location;
FVector TriA = Vertices[0];
FVector TriB = Vertices[1];
FVector TriC = Vertices[2];
FVector BarycentricCoords;

bool bInsideTriangle = UEurekaMathUtilityFunctionLibrary::PointInTriangle(
    ClickPosition, TriA, TriB, TriC, BarycentricCoords
);

if (bInsideTriangle)
{
    // BarycentricCoords can be used for interpolation
    FLinearColor InterpolatedColor = 
        ColorA * BarycentricCoords.X +
        ColorB * BarycentricCoords.Y +
        ColorC * BarycentricCoords.Z;
}
```

#### Ray-Triangle Intersection
```cpp
// Custom ray casting against triangle meshes
FVector RayOrigin = Camera->GetComponentLocation();
FVector RayDirection = Camera->GetForwardVector();
FVector HitPoint;
FVector BarycentricCoords;

bool bHit = UEurekaMathUtilityFunctionLibrary::RayTriangleIntersection(
    RayOrigin, RayDirection,
    TriangleP0, TriangleP1, TriangleP2,
    HitPoint, BarycentricCoords
);

if (bHit)
{
    // Use barycentric coords to interpolate vertex data (normals, UVs, etc.)
    FVector InterpolatedNormal = 
        Normal0 * BarycentricCoords.X +
        Normal1 * BarycentricCoords.Y +
        Normal2 * BarycentricCoords.Z;
}
```

## API Reference

### Easing Functions
All easing functions take a float parameter `f` in the range [0, 1] and return an eased value.

| Function | Description | Best For |
|----------|-------------|----------|
| `Linear(f)` | No easing | Constant speed animations |
| `EaseIn(f)` | Quadratic acceleration | Starting movements |
| `EaseOut(f)` | Quadratic deceleration | Stopping movements |
| `SmoothStep(f)` | Smooth start and stop | General animations |
| `EaseOutElastic(f)` | Elastic overshoot | Playful UI effects |
| `OutBounce(f)` | Bouncing deceleration | Landing effects |

### Geometric Functions

#### Angles
```cpp
float AngleBetween(FVector2D A, FVector2D B)
float SignedAngleBetween(FVector2D A, FVector2D B)
```

#### Segments & Lines
```cpp
FVector ClosestPointOnSegment(const FVector& Point, const FVector& SegmentStart, const FVector& SegmentEnd)
```

#### Planes
```cpp
bool GetSide(const FVector& Point, const FPlane& Plane)
FVector ClosestPointOnPlane(const FVector& Point, const FPlane& Plane)
```

#### Triangles
```cpp
bool PointInTriangle(const FVector& Point, const FVector& P0, const FVector& P1, const FVector& P2, FVector& OutBarycentricCoords)
bool RayTriangleIntersection(const FVector& RayOrigin, const FVector& RayDirection, const FVector& P0, const FVector& P1, const FVector& P2, FVector& OutHitPoint, FVector& OutBarycentricCoords)
```

## Blueprint Support

All functions are exposed to Blueprints with appropriate categories:
- **Eureka|Math|Easing** - Easing functions
- **Eureka|Math|Angle** - Angle calculations
- **Eureka|Math|Segment** - Line segment operations
- **Eureka|Math|Plane** - Plane operations
- **Eureka|Math|Triangle** - Triangle operations

## License

MIT License - See [LICENSE](LICENSE) file for details

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

<!-- ## Roadmap

- [ ] Additional easing functions (InOut variants, Cubic, Quartic, etc.)
- [ ] Circle-segment intersection
- [ ] Sphere-triangle intersection
- [ ] Capsule geometry utilities
- [ ] 3D angle calculations (for FVector) -->

## Credits

Created by Simon Kramer

Based on math utilities by Carl Granberg, converted from Unity/C# to Unreal Engine/C++.
