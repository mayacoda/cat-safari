
#ifndef SAFARI_MODEL_H
#define SAFARI_MODEL_H


#include <glm/vec3.hpp>
#include <list>
#include <glm/detail/type_mat4x4.hpp>
#include "../shaders/Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../texture/Texture.h"
#include "../util/Hexahedron.h"

struct BoundingBox {
    std::vector<glm::vec3> points;

    std::vector<glm::vec3> transformPoints(const glm::mat4 &modelMat) const {
        std::vector<glm::vec3> transformed;
        for (auto              it = points.begin(); it != points.end(); ++it) {
            transformed.push_back(glm::vec3(modelMat * glm::vec4((*it), 1)));
        }
        return transformed;
    }
};

class Model {
protected:
    VertexArray* m_va;
    IndexBuffer* m_ib;

    glm::vec3   m_origin;
    BoundingBox m_bb;

public:
    Model(VertexArray* m_va, IndexBuffer* m_ib);

    virtual ~Model();

    void setOrigin(const glm::vec3 &origin) { m_origin = origin; }

    void setBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    const VertexArray &getVertexArray() const { return *m_va; }

    const IndexBuffer &getIndexBuffer() const { return *m_ib; }

    const BoundingBox &getBoundingBox() const { return m_bb; }

    const glm::vec3 &getOrigin() const { return m_origin; }

    virtual void bind() const;

    virtual void unbind() const;
};


#endif //SAFARI_MODEL_H
