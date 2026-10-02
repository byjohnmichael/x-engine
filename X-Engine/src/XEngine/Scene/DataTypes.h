#pragma once
#include <glm/gtc/type_ptr.hpp>
namespace XEngine
{
	struct XVec2
	{
		float X, Y;
		operator glm::vec2() const
			{ return glm::vec2{X, Y}; }
	};
	struct XVec3
	{
		float X, Y, Z;
		operator glm::vec3() const
			{ return glm::vec3{X, Y, Z}; }
	};
	struct XVec4
	{
		float X, Y, Z, W;
		operator glm::vec4() const
			{ return glm::vec4{ X, Y, Z, W }; }
	};
	struct XColor3
	{
		float X, Y, Z;
		operator glm::vec3() const
			{ return glm::vec3{X, Y, Z}; }	};
	struct XColor4
	{
		float X, Y, Z, W;
		operator glm::vec4() const
			{ return glm::vec4{ X, Y, Z, W }; }	};
}

// byjohnmichael
