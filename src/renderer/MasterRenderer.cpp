
#include "MasterRenderer.h"

void MasterRenderer::render(const Light &light, const Camera &camera) {
    m_renderer.prepare();

    m_shader.bind();
    m_shader.loadLight(light);
    m_shader.loadViewMatrix(camera);

    m_renderer.render(m_entities);

    m_entities.clear();
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

    m_shader.unbind();
}
