#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"

#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera) {
	for (int y = 0; y < framebuffer.height; y++) {
		for (int x = 0; x < framebuffer.width; x++) {

			glm::vec2 pixel{ x, y };
			glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };
			// flip the y value (bottom = 0, top = 1)
			point.y = 1 - point.y;

			Ray ray = camera.GetRay(point);
			raycastHit_t raycastHit;

			color3_t color = Trace(ray, 0, 100, raycastHit);
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
	}
}

void Scene::AddObject(std::unique_ptr<Object> object) {
	objects.push_back(std::move(object));
}

color3_t Scene::Trace(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	bool rayHit = false;
	float closestDistance = maxDistance;

	for (auto& object : objects) {

			if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
				rayHit = true;
				closestDistance = raycastHit.distance;
			}
	}

	if (rayHit) {
		color3_t color = raycastHit.color;
		return color;
	}

	glm::vec3 direction = glm::normalize(ray.direction);

	float t = (direction.y + 1) * 0.5f;

	color3_t color = glm::mix(skyBottom, skyTop, t);
	return color;
}

