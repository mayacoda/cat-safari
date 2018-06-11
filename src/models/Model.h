
#ifndef SAFARI_MODEL_H
#define SAFARI_MODEL_H


#include "../shaders/Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../texture/Texture.h"

class Model {
protected:
    VertexArray * m_va;
    IndexBuffer * m_ib;

public:
    Model( VertexArray *m_va,  IndexBuffer *m_ib);

    virtual ~Model();

    const VertexArray &getVertexArray() const { return *m_va; }

    const IndexBuffer &getIndexBuffer() const { return *m_ib; }

    virtual void bind() const;

    virtual void unbind() const;
};


#endif //SAFARI_MODEL_H
