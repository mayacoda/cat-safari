
#ifndef SAFARI_MASTERRENDERER_H
#define SAFARI_MASTERRENDERER_H


#include <list>
#include <map>
#include "../shaders/Shader.h"
#include "Renderer.h"

class MasterRenderer {
private:
    StaticShader m_shader;
    Renderer     m_renderer;

    std::map<const TexturedModel*, std::list<Entity*> > m_entities;

public:
    MasterRenderer(const StaticShader &m_shader, const Renderer &m_renderer) : m_shader(m_shader),
                                                                               m_renderer(m_renderer) {}

    void render(const Light &light, const Camera &camera);

    void processEntity(Entity* entity);

    void cleanUp();

};


#endif //SAFARI_MASTERRENDERER_H
