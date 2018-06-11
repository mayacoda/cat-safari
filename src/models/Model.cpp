
#include "Model.h"

Model::Model( VertexArray *m_va,  IndexBuffer *m_ib) : m_va(m_va), m_ib(m_ib) {}

void Model::bind() const {
    m_va->bind();
    m_ib->bind();
}

void Model::unbind() const {
    m_va->unbind();
    m_ib->unbind();
}

Model::~Model() {
    delete m_va;
    delete m_ib;
}
