
#ifndef SAFARI_MODEL_H
#define SAFARI_MODEL_H


#include "../shaders/Shader.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include "../texture/Texture.h"

class Model {
protected:
    VertexArray m_va;
    IndexBuffer m_ib;

public:
    Model(const VertexArray &m_va, const IndexBuffer &m_ib);

    Model(const void* data,
          unsigned int size,
          unsigned int* indices,
          unsigned int count);

    const VertexArray &getVertexArray() const { return m_va; }

    const IndexBuffer &getIndexBuffer() const { return m_ib; }

    virtual Texture &getTexture() = 0;

    virtual const Texture &getTexture() const = 0;

    virtual void bind() const;

    virtual void unbind() const;
};


#endif //SAFARI_MODEL_H
