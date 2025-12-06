#pragma once
#include "Color.h"
#include <glm/glm.hpp>

struct Ray {
public:
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction)
		: origin(origin), direction(glm::normalize(direction)) {}

	glm::vec3 at(float t) const {
		return origin + t * direction;
	}

	glm::vec3 operator * (float t) const {
		return direction * t;
	}

	glm::vec3 origin{0.0f};
	glm::vec3 direction{0.0f, 0.0f, -1.0f};
};

struct raycastHit_t {
	glm::vec3 point;	
	glm::vec3 normal;	
	float distance;	

	color3_t color;	
};