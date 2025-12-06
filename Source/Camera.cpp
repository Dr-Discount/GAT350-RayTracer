#include "Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	this->forward = glm::normalize(target - eye);
	this->right = glm::normalize(glm::cross(this->forward, up));
	this->up = glm::normalize(glm::cross(this->right, this->forward));

	CalculateViewPlane();
}

Ray Camera::GetRay(const glm::vec2& uv) const {
	Ray ray;

	ray.origin = eye;
	ray.direction = glm::normalize(lowerLeft + (horizontal * uv.x) + (vertical * uv.y) - eye);

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = tan(theta / 2.0f);
	float halfWidth = aspectRatio * halfHeight;

	horizontal = right * (2.0f * halfWidth);
	vertical = up * (2.0f * halfHeight);

	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward;
}

