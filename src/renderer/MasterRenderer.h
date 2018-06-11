
#ifndef SAFARI_MASTERRENDERER_H
#define SAFARI_MASTERRENDERER_H


#include <list>
#include <map>
#include "../shaders/Shader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

class MasterRenderer {
private:
    StaticShader   * m_entityShader;
    EntityRenderer * m_entityRenderer;
    TerrainShader  * m_terrainShader;
    TerrainRenderer* m_terrainRenderer;

    glm::mat4 m_projectionMatrix;

    std::map<const TexturedModel*, std::list<Entity*> > m_entities;
    std::list<Terrain*> m_terrains;

public:
    MasterRenderer(int width, int height);

    virtual ~MasterRenderer();

    void render(const Light &light, const Camera &camera);

    void processEntity(Entity* entity);

    void processTerrain(Terrain* terrain);

    void cleanUp();

    void init();

    static void enableCulling() {
        debug(glEnable(GL_CULL_FACE));
        debug(glCullFace(GL_BACK));
    }

    static void disableCulling() {
        debug(glDisable(GL_CULL_FACE));
    }

};


#endif //SAFARI_MASTERRENDERER_H
