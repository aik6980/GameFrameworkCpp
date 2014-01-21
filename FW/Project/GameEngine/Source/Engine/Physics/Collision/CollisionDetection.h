#ifndef CollisionDetection_h__
#define CollisionDetection_h__

struct AABB2;
struct Circle;

class CCollisionDetection
{
	static bool Test(const AABB2& a, const AABB2& b); 
	static bool Test(const Circle& a, const Circle& b); 
};

#endif // CollisionDetection_h__
