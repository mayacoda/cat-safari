
#include "Model.h"

Model::Model(const Shader &m_shader, const VertexArray &m_va, const IndexBuffer &m_ib) : m_shader(m_shader),
                                                                                         m_va(m_va),
                                                                                         m_ib(m_ib) {}
