
#include "TerrainTexture.h"
#include "../util/GL.h"
#include "../../lib/stb_image.h"

TerrainTexture::TerrainTexture(const std::string &path) {
    debug(glGenTextures(1, &m_textureId));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));
    unsigned char* buffer;

    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
    if (!buffer) {
        std::cout << "[TerrainTexture::TerrainTexture] Cannot open texture file: " << path << std::endl;
    }

    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    debug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    debug(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));

    if (buffer) {
        stbi_image_free(buffer);
    }
}

void TerrainTexture::bind(unsigned int slot) const {
    debug(glActiveTexture(GL_TEXTURE0 + slot));
    debug(glBindTexture(GL_TEXTURE_2D, m_textureId));
}

void TerrainTexture::unbind() const {
    debug(glBindTexture(GL_TEXTURE_2D, 0));
}
