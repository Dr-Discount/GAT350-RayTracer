#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"

#include <iostream>
#include <random>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples) {
	for (int y = 0; y < framebuffer.height; y++) {
		for (int x = 0; x < framebuffer.width; x++) {

			color3_t color{ 0 };

			for (int i = 0; i < numSamples; i++) {
				glm::vec2 pixel{ x, y };

				//< add vec2{ random real 0 - 1, random real 0 - 1 } > ;
				pixel += glm::vec2{ static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX };

				glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };

				point.y = 1 - point.y;

				// get ray from camera
				Ray ray = camera.GetRay(point);
				raycastHit_t raycastHit;
				// trace ray
				color += Trace(ray, 0, 100, raycastHit);
			}
			// get average color = (color / number samples)
			color /= static_cast<float>(numSamples);
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

