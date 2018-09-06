
#ifndef SAFARI_HEXAHEDRON_H
#define SAFARI_HEXAHEDRON_H

#include <vector>
#include "Plane.h"

class Hexahedron {

    std::vector<Plane*> planes;

public:
    enum PLANES {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEAR,
        FAR
    };

    enum POINT_STATE {
        OUTSIDE, INTERSECT, INSIDE
    };

    Hexahedron();

    virtual ~Hexahedron();

    void setPlanePoints(PLANES plane, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3);

    void createFromBBPoints(std::vector<glm::vec3> points);

    POINT_STATE isInside(const glm::vec3 &point) const;
};


#endif //SAFARI_HEXAHEDRON_H
