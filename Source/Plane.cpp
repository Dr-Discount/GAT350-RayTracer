#include "Plane.h"
#include <glm/glm.hpp>
#include <limits>

bool Plane::Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
    float t;
    // transform position
    glm::vec3 center = glm::vec3(0.0f, -2.0f, 0.0f); // transform position
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f); // transform up vector
    // check ray intersection, returns true if ray intersects, t is distance to intersection
    if (!Raycast(ray, center, normal, minDistance, maxDistance, t)) return false;

    // set raycast parameters
    raycastHit.distance = t;
    raycastHit.point = ray.origin + t * ray.direction;
    raycastHit.normal = normal;
    raycastHit.material = this->material.get();

    return true;
}

bool Plane::Raycast(const Ray& ray, const glm::vec3& point, const glm::vec3& normal, float minDistance, float maxDistance, float& t)
{
    // check dot product of ray direction and plane normal, if result is 0 then ray direction is parallel to plane
    float denominator = glm::dot(ray.direction, normal);
    // Use std::numeric_limits<float>::epsilon() instead of glm::epsilon<float>()
    if (std::abs(denominator) < std::numeric_limits<float>::epsilon()) {
        return false;
    }

    // Solve for t in the ray–plane intersection equation:
    //     (planePoint - rayOrigin) · planeNormal
    // t = ----------------------------------------
    //           rayDirection · planeNormal
    t = glm::dot(point - ray.origin, normal) / denominator;

    // return true if within distance bounds
    return (t > minDistance && t < maxDistance);
}
