
#ifndef SAFARI_FRUSTUM_H
#define SAFARI_FRUSTUM_H

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_map>
#include <vector>

struct Plane {
    glm::vec3 normal;
    glm::vec3 point;

    void setPoints(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
        auto temp1 = p1 - p2;
        auto temp2 = p3 - p2;

        normal = glm::normalize(glm::cross(temp2, temp1));
        point  = p2;
    }

    Plane() {
        normal = glm::vec3(0);
        point  = glm::vec3(0);
    }

    float distance(const glm::vec3 &p0) const {
        return glm::dot(normal, (p0 - point));
    }
};

class Frustum {
private:
    enum PLANES {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEAR,
        FAR
    };

public:

    Frustum();

    virtual ~Frustum();

    enum POINT_STATE {
        OUTSIDE, INTERSECT, INSIDE
    };

    glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
    float     nearD, farD, ratio, angle, tang;
    float     nw, nh, fw, fh;

    std::vector<Plane *> planes;

    void setCameraInternals(float angle, float ratio, float nearD, float farD);

    void setCameraDef(const glm::vec3 &position, const glm::vec3 &lookAt, const glm::vec3 &up);

    POINT_STATE pointInFrustum(const glm::vec3 &point) const;
};


#endif //SAFARI_FRUSTUM_H
