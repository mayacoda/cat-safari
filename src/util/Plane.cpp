
#include <glm/geometric.hpp>
#include "Plane.h"

void Plane::setPoints(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
    auto temp1 = p1 - p2;
    auto temp2 = p3 - p2;

    normal = glm::normalize(glm::cross(temp2, temp1));
    point  = p2;
}

float Plane::distance(const glm::vec3 &p0) const {
    return glm::dot(normal, (p0 - point));
}
