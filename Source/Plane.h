#pragma once
#include "Object.h"

class Plane : public Object
{
public:
	Plane() = default;
	Plane(std::shared_ptr<Material> material) :
		Object{ material }		
	{}

	bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

	// check ray to plane intersection, returns true if ray intersects, t is distance to intersection
	static bool Raycast(const Ray& ray, 
						const glm::vec3& point, 
						const glm::vec3& normal, 
						float minDistance, 
						float maxDistance, 
						float& t);
};