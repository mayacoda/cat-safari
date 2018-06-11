
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
    MasterRenderer(int width, int height) {
        init();
        m_projectionMatrix = createProjectionMatrix(width, height);

        m_entityShader    = new StaticShader();
        m_entityRenderer  = new EntityRenderer(m_entityShader, m_projectionMatrix);

        m_terrainShader   = new TerrainShader();
        m_terrainRenderer = new TerrainRenderer(m_terrainShader, m_projectionMatrix);
    }

    virtual ~MasterRenderer() {
        delete m_entityShader;
        delete m_entityRenderer;

        delete m_terrainShader;
        delete m_terrainRenderer;
    }

    void render(const Light &light, const Camera &camera);

    void processEntity(Entity* entity);

    void processTerrain(Terrain* terrain);

    void cleanUp();

    void init();

};


#endif //SAFARI_MASTERRENDERER_H
