
#ifndef SAFARI_MODEL_H
#define SAFARI_MODEL_H


#include "../shaders/Shader.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"

class Model {
private:
    Shader      m_shader;
    VertexArray m_va;
    IndexBuffer m_ib;

public:
    Model(const Shader &m_shader, const VertexArray &m_va, const IndexBuffer &m_ib);

    const Shader getShader() const { return m_shader; }

    const VertexArray getVertexArray() const { return m_va; }

    const IndexBuffer getIndexBuffer() const { return m_ib; }
};


#endif //SAFARI_MODEL_H
