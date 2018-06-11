
#ifndef SAFARI_TERRAINTEXTUREPACK_H
#define SAFARI_TERRAINTEXTUREPACK_H


#include "TerrainTexture.h"

class TerrainTexturePack {
private:
    TerrainTexture * m_backgroundTexture;
    TerrainTexture * m_rTexture;
    TerrainTexture * m_gTexture;
    TerrainTexture * m_bTexture;

public:
    TerrainTexturePack(const std::string &background,const std::string &red,const std::string &green,const std::string &blue) {
        m_backgroundTexture = new TerrainTexture("./res/textures/" + background + ".png");
        m_rTexture = new TerrainTexture("./res/textures/" + red + ".png");
        m_gTexture = new TerrainTexture("./res/textures/" + green + ".png");
        m_bTexture = new TerrainTexture("./res/textures/" + blue + ".png");
    }

    TerrainTexture* getBackgroundTexture() const {
        return m_backgroundTexture;
    }

    TerrainTexture* getRTexture() const {
        return m_rTexture;
    }

    TerrainTexture* getGTexture() const {
        return m_gTexture;
    }

    TerrainTexture* getBTexture() const {
        return m_bTexture;
    }

    void bind() {
        m_backgroundTexture->bind();
        m_rTexture->bind(1);
        m_gTexture->bind(2);
        m_bTexture->bind(3);
    }

    void unbind() {
        m_backgroundTexture->unbind();
        m_rTexture->unbind();
        m_gTexture->unbind();
        m_bTexture->unbind();
    }
};


#endif //SAFARI_TERRAINTEXTUREPACK_H
