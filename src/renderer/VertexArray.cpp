
#include "VertexArray.h"

VertexArray::VertexArray() {
    debug(glGenVertexArrays(1, &m_vaoId));
}

VertexArray::~VertexArray() {
    debug(glDeleteVertexArrays(1, &m_vaoId));
    std::cout << "[VertexArray::~VertexArray]" << std::endl;
}

void VertexArray::addBuffer(const VertexBuffer &vb, const BufferLayout &layout) {
    bind();
    vb.bind();

    const auto   &elements = layout.getElements();
    unsigned int offset    = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];

        debug(glEnableVertexAttribArray(i));
        debug(glVertexAttribPointer(i,
                                    element.count,
                                    element.type,
                                    element.normalized,
                                    layout.getStride(),
                                    (const void*) offset));

        offset += element.count * GL::typeToSizeOf(element.type);
    }
}

void VertexArray::bind() const {
    debug(glBindVertexArray(m_vaoId));

}

void VertexArray::unbind() const {
    debug(glBindVertexArray(0));
}
