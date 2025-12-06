#pragma once
#include "Ray.h"
#include "Color.h"

class Object
{
public:
	Object() = default;
	Object(const color3_t& color) {
		this->color = color;
	}

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

protected:
	color3_t color;
};