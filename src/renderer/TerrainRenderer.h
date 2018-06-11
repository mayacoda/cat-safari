
#ifndef SAFARI_TERRAINRENDERER_H
#define SAFARI_TERRAINRENDERER_H


#include <glm/detail/type_mat4x4.hpp>
#include <list>
#include "../shaders/TerrainShader.h"
#include "../world/Terrain.h"
#include "../util/geometry.h"

class TerrainRenderer {
private:

    TerrainShader* m_shader;

    void loadModelMatrix(Terrain* terrain) const;

public:
    TerrainRenderer(TerrainShader* shader, glm::mat4 matrix);

    void render(std::list<Terrain*> terrains) const;

};


#endif //SAFARI_TERRAINRENDERER_H
