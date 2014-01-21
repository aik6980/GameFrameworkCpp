#include "stdafx.h"
#include "CollisionDetection.h"

#include "BoundingVolume.h"

bool CCollisionDetection::Test( const AABB2& a, const AABB2& b )
{
	// Exit with no intersection if found separated along an axis
	if(a.Max.x < b.Min.x || a.Min.x > b.Max.x) return false;
	if(a.Max.y < b.Min.y || a.Min.y > b.Max.y) return false;
	// No separating axis found, therefor there is at least one overlapping axis
	return true;
}

bool CCollisionDetection::Test( const Circle& a, const Circle& b )
{
	float rSq = a.Radius - b.Radius;
	rSq *= rSq;

	// Dor product -> (a.Center - b.Center).Length()^2
	float distSq = glm::dot( a.Center, b.Center);
	return ( rSq < distSq ); 
}

