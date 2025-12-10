#pragma once
#include "Ray.h"
#include "Color.h"
#include "Material.h"

class Object
{
public:
	Object() = default;
	Object(std::shared_ptr<Material> material) {
		this->material = material;
	}

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

protected:
	//color3_t color;
	std::shared_ptr<Material> material;
};