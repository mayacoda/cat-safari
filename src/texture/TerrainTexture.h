
#ifndef SAFARI_TERRAINTEXTURE_H
#define SAFARI_TERRAINTEXTURE_H


#include <string>

class TerrainTexture {
private:
    unsigned int m_textureId;
    int m_width, m_height, m_bpp;

public:
    TerrainTexture(const std::string &path);

    void bind(unsigned int slot = 0) const;

    void unbind() const;
};


#endif //SAFARI_TERRAINTEXTURE_H
