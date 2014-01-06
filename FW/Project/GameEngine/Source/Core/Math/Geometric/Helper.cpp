#include "stdafx.h"
#include "Helper.h"

float BasicMath::EPSILON = glm::epsilon<float>();
float BasicMath::PI = glm::pi<float>();
float BasicMath::PIDiv2 = glm::half_pi<float>();

glm::vec3 GeomMath::ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 GeomMath::UNIT_X = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 GeomMath::UNIT_Y = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 GeomMath::UNIT_Z = glm::vec3(0.0f, 0.0f, 1.0f);

glm::mat4 GeomMath::CreateLookAtMatrix( const glm::vec3& _eyePos, const glm::vec3& _targetPos, const glm::vec3& _upDir /*= UNIT_Y*/ )
{
	glm::mat4 m = glm::lookAt(_eyePos, _targetPos, _upDir);
	return m;
}

glm::mat4 GeomMath::CreateProjPerspective( float _radFov, float _aspect, float _znear, float _zfar )
{
	glm::mat4 m = glm::perspective(_radFov, _aspect, _znear, _zfar);
	return m;
}

void GeomMath::DecomposeMatrix( glm::mat3& _oRot, glm::vec3& _oTx, const glm::mat4& _val )
{
	_oRot = glm::mat3(_val);
	_oTx  = glm::vec3(_val[4]);
}

glm::mat4 GeomMath::CreateFromQuat( const glm::quat& _val )
{
	return glm::toMat4(_val);
}











