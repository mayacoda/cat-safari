
#include "MasterRenderer.h"

void MasterRenderer::render(const Light &light, const Camera &camera) {
    debug(glClearColor(.6, .8, .9, 1));
    debug(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_entityShader->bind();
    m_entityShader->loadLight(light);
    m_entityShader->loadViewMatrix(camera);
    m_entityRenderer->render(m_entities);

    m_entityShader->unbind();

    m_terrainShader->bind();
    m_terrainShader->loadLight(light);
    m_terrainShader->loadViewMatrix(camera);
    m_terrainRenderer->render(m_terrains);
    m_terrainShader->unbind();

    m_entities.clear();
    m_terrains.clear();
}

void MasterRenderer::processEntity(Entity* entity) {
    const TexturedModel &model = entity->getModel();
    const TexturedModel* ptr = &model;

    if (m_entities.find(ptr) != m_entities.end()) {
        m_entities[ptr].push_back(entity);
    } else {
        m_entities[ptr] = std::list<Entity*>();
        m_entities[ptr].push_back(entity);
    }
}

void MasterRenderer::cleanUp() {

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        const TexturedModel* const model = it->first;
        model->unbind();
    }

    m_entityShader->unbind();
    m_terrainShader->unbind();
}

void MasterRenderer::init() {
    debug(glEnable(GL_DEPTH_TEST));
    debug(glEnable(GL_BLEND));
    debug(glEnable(GL_CULL_FACE));
    debug(glCullFace(GL_BACK));
    debug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void MasterRenderer::processTerrain(Terrain* terrain) {
    m_terrains.push_back(terrain);
}
