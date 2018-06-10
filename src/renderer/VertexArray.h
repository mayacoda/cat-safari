
#ifndef SAFARI_VERTEXARRAY_H
#define SAFARI_VERTEXARRAY_H


#include "BufferLayout.h"
#include "VertexBuffer.h"

class VertexArray {
private:
    unsigned int m_vaoId;
public:

    VertexArray();

    ~VertexArray();

    void addBuffer(const VertexBuffer &vb, const BufferLayout &layout);

    unsigned int getId() const { return m_vaoId; }

    void bind() const;

    void unbind() const;
};


#endif //SAFARI_VERTEXARRAY_H
