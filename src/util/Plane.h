
#ifndef SAFARI_PLANE_H
#define SAFARI_PLANE_H

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

struct Plane {
    glm::vec3 normal;
    glm::vec3 point;

    void setPoints(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3);

    Plane() {
        normal = glm::vec3(0);
        point  = glm::vec3(0);
    }

    float distance(const glm::vec3 &p0) const;
};


#endif //SAFARI_PLANE_H
