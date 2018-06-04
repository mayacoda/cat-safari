
#include <GL/glew.h>
#include "Texture.h"

#include "../../lib/stb_image.h"
#include "../util/GL.h"

Texture::Texture(const std::string &path) : m_textureId(0),
                                            m_filePath(path),
                                            m_buffer(nullptr),
                                            m_width(0),
                                            m_height(0),
                                            m_bpp(0) {
    debug(glGenTextures(1, &m_textureId));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));

    stbi_set_flip_vertically_on_load(1);
    m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    debug(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));


    debug(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_buffer) {
        stbi_image_free(m_buffer);
    }
}

Texture::~Texture() {
    debug(glDeleteTextures(1, &m_textureId));
}

void Texture::bind(unsigned int slot) const {
    debug(glActiveTexture(GL_TEXTURE0 + slot));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));

}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);

}
