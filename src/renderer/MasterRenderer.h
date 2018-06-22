
#ifndef SAFARI_MASTERRENDERER_H
#define SAFARI_MASTERRENDERER_H


#include <list>
#include <map>
#include "../shaders/Shader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "GUIRenderer.h"
#include "../world/GUI.h"

class MasterRenderer {
private:
    StaticShader   * m_entityShader;
    EntityRenderer * m_entityRenderer;
    TerrainShader  * m_terrainShader;
    TerrainRenderer* m_terrainRenderer;
    GUIRenderer    * m_guiRenderer;

    glm::mat4 m_projectionMatrix;

    std::map<const TexturedModel*, std::list<Entity*> > m_entities;
    std::list<Terrain*>                                 m_terrains;

    int m_width;
    int m_height;

public:
    MasterRenderer(int width, int height);

    virtual ~MasterRenderer();

    void render(const Light &light, const Camera &camera, const GUI &gui);

    void processEntity(Entity* entity);

    void processTerrain(Terrain* terrain);

    void cleanUp();

    void init();

    void togglePhotoView(Camera* camera);

    static void enableCulling() {
        debug(glEnable(GL_CULL_FACE));
        debug(glCullFace(GL_BACK));
    }

    static void disableCulling() {
        debug(glDisable(GL_CULL_FACE));
    }

    glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }

};


#endif //SAFARI_MASTERRENDERER_H
