
#include "Hexahedron.h"

Hexahedron::Hexahedron() {
    planes.reserve(6);
    for (int i = 0; i < 6; i++) {
        planes.push_back(new Plane());
    }
}

Hexahedron::~Hexahedron() {
    for (auto it = planes.begin(); it != planes.end(); ++it) {
        delete *it;
    }
}

void Hexahedron::setPlanePoints(Hexahedron::PLANES plane,
                                const glm::vec3 &p1,
                                const glm::vec3 &p2,
                                const glm::vec3 &p3) {
    planes[plane]->setPoints(p1, p2, p3);
}

Hexahedron::POINT_STATE Hexahedron::isInside(const glm::vec3 &point) const {
    for (auto it = planes.begin(); it != planes.end(); ++it) {
        float d = (*it)->distance(point);

        if (d < 0) {
            return OUTSIDE;
        }
        if (d == 0) {
            return INTERSECT;
        }
    }

    return INSIDE;
}

void Hexahedron::createFromBBPoints(std::vector<glm::vec3> points) {
    glm::vec3 rtf, rbf, rtb, rbb, ltf, lbf, ltb, lbb;
    rtf = points.at(0);
    rbf = points.at(1);
    rtb = points.at(2);
    rbb = points.at(3);
    ltf = points.at(4);
    lbf = points.at(5);
    ltb = points.at(6);
    lbb = points.at(7);

    setPlanePoints(Hexahedron::TOP, rtf, ltf, ltb);
    setPlanePoints(Hexahedron::BOTTOM, lbf, rbf, rbb);
    setPlanePoints(Hexahedron::LEFT, ltf, lbf, lbb);
    setPlanePoints(Hexahedron::RIGHT, rtf, rtb, rbb);
    setPlanePoints(Hexahedron::NEAR, ltf, rtf, rbf);
    setPlanePoints(Hexahedron::FAR, rtb, ltb, lbb);
}

