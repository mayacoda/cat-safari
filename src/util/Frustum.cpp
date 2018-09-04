
#include <iostream>
#include "Frustum.h"

void Frustum::setCameraInternals(float angle, float ratio, float nearD, float farD) {
    this->angle = angle;
    this->ratio = ratio;
    this->nearD = nearD;
    this->farD  = farD;

    tang = static_cast<float>(tan(glm::radians(angle) * 0.5));

    nh = nearD * tang;
    nw = nh * ratio;

    fh = farD * tang;
    fw = fh * ratio;
}

void Frustum::setCameraDef(const glm::vec3 &position, const glm::vec3 &lookAt, const glm::vec3 &up) {
    glm::vec3 direction, nc, fc, x, y, z;

    z = glm::normalize(position - lookAt);

    x = glm::normalize(glm::cross(up, z));

    y = glm::cross(z, x);

    nc = position - z * nearD;
    fc = position - z * farD;

    ntl = nc + y * nh - x * nw;
    ntr = nc + y * nh + x * nw;
    nbl = nc - y * nh - x * nw;
    nbr = nc - y * nh + x * nw;

    ftl = fc + y * fh - x * fw;
    ftr = fc + y * fh + x * fw;
    fbl = fc - y * fh - x * fw;
    fbr = fc - y * fh + x * fw;

    planes[TOP]->setPoints(ntr, ntl, ftl);
    planes[BOTTOM]->setPoints(nbl, nbr, fbr);
    planes[LEFT]->setPoints(ntl, nbl, fbl);
    planes[RIGHT]->setPoints(ntr, ftr, fbr);
    planes[NEAR]->setPoints(ntl, ntr, nbr);
    planes[FAR]->setPoints(ftr, ftl, fbl);
}

Frustum::POINT_STATE Frustum::pointInFrustum(const glm::vec3 &point) const {

    int       i  = 0;
    for (auto it = planes.begin(); it != planes.end(); ++it) {
        float d = (*it)->distance(point);

        if (d < 0) {
            return OUTSIDE;
        }
        if (d == 0) {
            return INTERSECT;
        }
        ++i;
    }

    return INSIDE;
}

Frustum::Frustum() {
    planes.reserve(6);
    for (int i = 0; i < 6; i++) {
        planes.push_back(new Plane());
    }
}

Frustum::~Frustum() {
    for (auto it = planes.begin(); it != planes.end(); ++it) {
        delete *it;
    }
}
