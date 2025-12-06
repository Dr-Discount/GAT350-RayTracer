#pragma once
#include "Color.h"
#include "Ray.h"
#include "Object.h"
#include <vector>
#include <memory>

class Scene
{
public:
	Scene() = default;

	void Render(class Framebuffer& framebuffer, const class Camera& camera, int numSamples = 10);
	void SetSky(const color3_t& skyBottom, const color3_t& skyTop) {
		this->skyBottom = skyBottom;
		this->skyTop = skyTop;
	}

	void AddObject(std::unique_ptr<Object> object);

private:
	color3_t Trace(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit);

private:
	color3_t skyBottom{ 0, 0, 1 };
	color3_t skyTop{ 0, 1, 0 };

	std::vector<std::unique_ptr<class Object>> objects;
};