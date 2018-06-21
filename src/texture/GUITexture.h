
#ifndef SAFARI_GUITEXTURE_H
#define SAFARI_GUITEXTURE_H


#include <glm/vec2.hpp>
#include "Texture.h"

class GUITexture {
private:
    glm::vec2 m_pos;
    Texture* m_texture;

public:
    GUITexture(const glm::vec2 &m_pos, Texture* m_texture) : m_pos(m_pos), m_texture(m_texture) {}

    const glm::vec2 &getPos() const {
        return m_pos;
    }

    Texture* getTexture() const {
        return m_texture;
    }
};


#endif //SAFARI_GUITEXTURE_H
