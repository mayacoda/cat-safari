
#ifndef SAFARI_FRUSTUM_H
#define SAFARI_FRUSTUM_H

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_map>
#include <vector>
#include "Plane.h"
#include "Hexahedron.h"

class Frustum {
private:
    Hexahedron * m_hexahedron;
public:

    Frustum();

    virtual ~Frustum();

    glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
    float     nearD, farD, ratio, angle, tang;
    float     nw, nh, fw, fh;

    void setCameraInternals(float angle, float ratio, float nearD, float farD);

    void setCameraDef(const glm::vec3 &position, const glm::vec3 &lookAt, const glm::vec3 &up);

    Hexahedron::POINT_STATE pointInFrustum(const glm::vec3 &point) const;
};


#endif //SAFARI_FRUSTUM_H
