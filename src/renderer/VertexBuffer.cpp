
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "../util/GL.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {

    debug(glGenBuffers(1, &m_vboId));
    debug(glBindBuffer(GL_ARRAY_BUFFER, m_vboId));
    // @todo abstract GL_STATIC_DRAW because for some models it will be dynamic
    debug(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    debug(glDeleteBuffers(1, &m_vboId));
}

void VertexBuffer::bind() const {
    debug(glBindBuffer(GL_ARRAY_BUFFER, m_vboId));
}

void VertexBuffer::unbind() const  {
    debug(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

