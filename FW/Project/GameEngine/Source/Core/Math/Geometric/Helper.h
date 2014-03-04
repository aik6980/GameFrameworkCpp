#pragma once
#ifndef Geometric_Helper_h__
#define Geometric_Helper_h__

#include "Core/Math/Math.h"

class BasicMath
{
public:
	static float EPSILON;
	static float PI;
	static float PIDiv2;

	template<class T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + t * (b-a);
	}
};

class GeomMath
{
public:
	static glm::vec3 ORIGIN;
	static glm::vec3 UNIT_X;
	static glm::vec3 UNIT_Y;
	static glm::vec3 UNIT_Z;

	static glm::mat4	CreateLookAtMatrix(const glm::vec3& _eyePos, const glm::vec3& _targetPos, const glm::vec3& _upDir = UNIT_Y);
	static glm::mat4	CreateProjPerspective(float _radFov, float _aspect, float _znear, float _zfar);

	static void			DecomposeMatrix(glm::mat3& _oRot, glm::vec3& _oTx, const glm::mat4& _val);

	static glm::mat4	CreateFromQuat(const glm::quat& _val);
	
	static glm::vec3	Right(const glm::mat4& m)	{ return glm::vec3(m[0]); }
	static glm::vec3	Up(const glm::mat4& m)		{ return glm::vec3(m[1]); }
	// using OpenGL convention here, we are looking down -z axis (assuming we are looking into the screen, x-right y-up)
	static glm::vec3	Forward(const glm::mat4& m) { return -glm::vec3(m[2]); }
};

#endif // Helper_h__