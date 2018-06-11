
#include <GL/glew.h>
#include "IndexBuffer.h"
#include "../util/GL.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count) {

    debug(glGenBuffers(1, &m_iboId));
    debug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId));
    debug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    debug(glDeleteBuffers(1, &m_iboId));
    std::cout << "[IndexBuffer::~IndexBuffer]" << std::endl;
}

void IndexBuffer::bind() const {
    debug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId));
}

void IndexBuffer::unbind() const {
    debug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

