
#include "Model.h"

Model::Model( VertexArray *m_va,  IndexBuffer *m_ib) : m_va(m_va), m_ib(m_ib) {}

void Model::bind() const {
    m_va->bind();
    m_ib->bind();
}

void Model::unbind() const {
    m_va->unbind();
    m_ib->unbind();
}

Model::~Model() {
    delete m_va;
    delete m_ib;
}

void Model::setBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    m_bb.points.push_back(glm::vec3(maxX, maxY, maxZ)); // right top front
    m_bb.points.push_back(glm::vec3(maxX, minY, maxZ)); // right bottom front
    m_bb.points.push_back(glm::vec3(maxX, maxY, minZ)); // right top back
    m_bb.points.push_back(glm::vec3(maxX, minY, minZ)); // right bottom back
    m_bb.points.push_back(glm::vec3(minX, maxY, maxZ)); // left top front
    m_bb.points.push_back(glm::vec3(minX, minY, maxZ)); // left bottom front
    m_bb.points.push_back(glm::vec3(minX, maxY, minZ)); // left top back
    m_bb.points.push_back(glm::vec3(minX, minY, minZ)); // left bottom back
}
