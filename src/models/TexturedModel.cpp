
#include "TexturedModel.h"

TexturedModel::TexturedModel(
        VertexArray *m_va,
        IndexBuffer *m_ib,
        Texture *m_texture) : Model(m_va, m_ib),
                                    m_texture(m_texture) {
}


Texture &TexturedModel::getTexture() {
    return *m_texture;
}

const Texture &TexturedModel::getTexture() const {
    return *m_texture;
}

void TexturedModel::bind() const {
    Model::bind();

    m_texture->bind();
}

void TexturedModel::unbind() const {
    Model::unbind();
    m_texture->unbind();
}

bool TexturedModel::operator==(const TexturedModel &rhs) const {
    return rhs.getTexture().getId() == m_texture->getId() &&
           rhs.getIndexBuffer().getId() == m_ib->getId() &&
           rhs.getVertexArray().getId() == m_va->getId();
}

bool TexturedModel::operator!=(const TexturedModel &rhs) const {
    return !(rhs == *this);
}

bool TexturedModel::operator<(const TexturedModel &rhs) const {
    return m_texture->getId() < rhs.m_texture->getId();
}

bool TexturedModel::operator>(const TexturedModel &rhs) const {
    return rhs < *this;
}

bool TexturedModel::operator<=(const TexturedModel &rhs) const {
    return !(rhs < *this);
}

bool TexturedModel::operator>=(const TexturedModel &rhs) const {
    return !(*this < rhs);
}

TexturedModel::~TexturedModel() {
    delete m_texture;
}
