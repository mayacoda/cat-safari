
#ifndef SAFARI_MODEL_H
#define SAFARI_MODEL_H


#include <glm/vec3.hpp>
#include "../shaders/Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../texture/Texture.h"

struct BoundingBox{
    glm::vec3 min;
    glm::vec3 max;
};

class Model {
protected:
    VertexArray* m_va;
    IndexBuffer* m_ib;

    glm::vec3 m_origin;
    BoundingBox m_bb;

public:
    Model(VertexArray* m_va, IndexBuffer* m_ib);

    virtual ~Model();

    void setOrigin(const glm::vec3 &origin) { m_origin = origin; }

    void setBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
        m_bb.max = glm::vec3(maxX, maxY, maxZ);
        m_bb.min = glm::vec3(minX, minY, minZ);
    }

    const VertexArray &getVertexArray() const { return *m_va; }

    const IndexBuffer &getIndexBuffer() const { return *m_ib; }

    const BoundingBox &getBoundingBox() const { return m_bb; }

    virtual void bind() const;

    virtual void unbind() const;
};


#endif //SAFARI_MODEL_H
