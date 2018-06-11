
#ifndef SAFARI_TERRAIN_H
#define SAFARI_TERRAIN_H


#include "../models/TexturedModel.h"
#include "../util/fileUtil.h"
#include "../texture/TerrainTexturePack.h"

class Terrain {
private:
    const static float SIZE         = 800;
    const static int   VERTEX_COUNT = 128;

    float m_x;
    float m_z;

    Model* m_model;
    TerrainTexturePack* m_texturePack;
    TerrainTexture * m_blendMap;

    Model* generateTerrain();

public:

    Terrain(int gridX, int gridZ) : m_x(gridX * Terrain::SIZE), m_z(gridZ * Terrain::SIZE) {
        m_model = generateTerrain();
        m_texturePack = new TerrainTexturePack("grass", "gravel", "terrain2", "road");
        m_blendMap = new TerrainTexture("./res/blend_map.png");
    }

    float getX() const { return m_x; }

    float getZ() const { return m_z; }

    Model* getModel() const { return m_model; }

    TerrainTexturePack* getTexture() const { return m_texturePack; }

    TerrainTexture* getBlendMap() const { return m_blendMap; }
};


#endif //SAFARI_TERRAIN_H
