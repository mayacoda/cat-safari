
#include "Model.h"

Model::Model(const VertexArray &m_va, const IndexBuffer &m_ib) : m_va(m_va),
                                                                 m_ib(m_ib) {}

void Model::bind() const {
    m_va.bind();
    m_ib.bind();
}

Model::Model(const void* data,
             unsigned int size,
             unsigned int* indices,
             unsigned int count) : m_ib(indices, count) {

    VertexBuffer vb(data, size);

    BufferLayout layout;
    layout.pushFloat(3, "position");
    layout.pushFloat(2, "textureCoords");
    layout.pushFloat(3, "normals");
    m_va.addBuffer(vb, layout);
}

void Model::unbind() const {
    m_va.unbind();
    m_ib.unbind();
}