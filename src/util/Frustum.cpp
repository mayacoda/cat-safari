
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

    m_hexahedron->setPlanePoints(Hexahedron::TOP, ntr, ntl, ftl);
    m_hexahedron->setPlanePoints(Hexahedron::BOTTOM, nbl, nbr, fbr);
    m_hexahedron->setPlanePoints(Hexahedron::LEFT, ntl, nbl, fbl);
    m_hexahedron->setPlanePoints(Hexahedron::RIGHT, ntr, ftr, fbr);
    m_hexahedron->setPlanePoints(Hexahedron::NEAR, ntl, ntr, nbr);
    m_hexahedron->setPlanePoints(Hexahedron::FAR, ftr, ftl, fbl);
}

Hexahedron::POINT_STATE Frustum::pointInFrustum(const glm::vec3 &point) const {
    return m_hexahedron->isInside(point);
}

Frustum::Frustum() {
    m_hexahedron = new Hexahedron();
}

Frustum::~Frustum() {
    delete m_hexahedron;
}
