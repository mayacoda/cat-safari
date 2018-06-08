
#include "TexturedModel.h"

TexturedModel::TexturedModel(
                             const VertexArray &m_va,
                             const IndexBuffer &m_ib,
                             const Texture &m_texture) : Model(m_va, m_ib),
                                                         m_texture(m_texture) {}


const Texture &TexturedModel::getTexture() const {
    return m_texture;
}

void TexturedModel::render() const {
    Model::render();

    m_texture.bind();
}

TexturedModel::TexturedModel(const void* data,
                             unsigned int size,
                             unsigned int* indices,
                             unsigned int count,
                             const Texture &texture): Model(data, size, indices, count), m_texture(texture) {

}
