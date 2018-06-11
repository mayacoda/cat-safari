
#include <GL/glew.h>
#include "Texture.h"

#include "../../lib/stb_image.h"
#include "../util/GL.h"

Texture::Texture(const std::string &path, bool tile) : m_textureId(0),
                                            m_filePath(path),
                                            m_buffer(nullptr),
                                            m_width(0),
                                            m_height(0),
                                            m_bpp(0) {
    debug(glGenTextures(1, &m_textureId));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));

    stbi_set_flip_vertically_on_load(1);
    m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
    if (!m_buffer) {
        std::cout << "[Texture::Texture] Cannot open texture file: " << path << std::endl;
    }

    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tile ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tile ? GL_REPEAT : GL_CLAMP_TO_EDGE));

    debug(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));


    debug(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_buffer) {
        stbi_image_free(m_buffer);
    }
}

Texture::~Texture() {
    debug(glDeleteTextures(1, &m_textureId));
    std::cout << "[Texture::~Texture]" << std::endl;
}

float Texture::getShineDamper() const {
    return m_shineDamper;
}

void Texture::setShineDamper(float shineDamper) {
    m_shineDamper = shineDamper;
}

float Texture::getReflectivity() const {
    return m_reflectivity;
}

void Texture::setReflectivity(float reflectivity) {
    m_reflectivity = reflectivity;
}

void Texture::bind(unsigned int slot) const {
    debug(glActiveTexture(GL_TEXTURE0 + slot));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));
}

void Texture::unbind() const {
    debug(glBindTexture(GL_TEXTURE_2D, 0));

}
