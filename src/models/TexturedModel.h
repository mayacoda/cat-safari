
#ifndef SAFARI_TEXTUREDMODEL_H
#define SAFARI_TEXTUREDMODEL_H


#include "Model.h"
#include "../texture/Texture.h"

class TexturedModel: public Model {
private:
    Texture m_texture;

public:
    TexturedModel(const VertexArray &m_va, const IndexBuffer &m_ib, const Texture &m_texture);

    TexturedModel(const void* data, unsigned int size, unsigned int *indices, unsigned int count, const Texture &m_texture);

    Texture &getTexture();

    const Texture &getTexture() const override;

    void render() const;
};


#endif //SAFARI_TEXTUREDMODEL_H
