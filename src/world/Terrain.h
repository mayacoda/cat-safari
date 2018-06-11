
#ifndef SAFARI_TERRAIN_H
#define SAFARI_TERRAIN_H


#include "../models/TexturedModel.h"
#include "../util/fileUtil.h"

class Terrain {
private:
    const static float SIZE         = 800;
    const static int   VERTEX_COUNT = 128;

    float m_x;
    float m_z;

    TexturedModel* m_model;

    TexturedModel* generateTerrain();

public:

    Terrain(int gridX, int gridZ) : m_x(gridX * Terrain::SIZE), m_z(gridZ * Terrain::SIZE) {
        m_model = generateTerrain();
    }

    float getX() const { return m_x; }

    float getZ() const { return m_z; }

    TexturedModel* getModel() const { return m_model; }

};


#endif //SAFARI_TERRAIN_H
