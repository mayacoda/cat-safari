
#ifndef SAFARI_TEXTUREDMODEL_H
#define SAFARI_TEXTUREDMODEL_H


#include "Model.h"
#include "../texture/Texture.h"

class TexturedModel: public Model {
private:
    Texture *m_texture;

public:
    TexturedModel( VertexArray *m_va,  IndexBuffer *m_ib,  Texture *m_texture);

    Texture &getTexture();

    virtual ~TexturedModel();

    const Texture &getTexture() const override;

    void bind() const;

    void unbind() const override;

    bool operator==(const TexturedModel &rhs) const;

    bool operator!=(const TexturedModel &rhs) const;

    bool operator<(const TexturedModel &rhs) const;

    bool operator>(const TexturedModel &rhs) const;

    bool operator<=(const TexturedModel &rhs) const;

    bool operator>=(const TexturedModel &rhs) const;
};


#endif //SAFARI_TEXTUREDMODEL_H
