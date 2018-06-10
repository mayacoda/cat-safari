
#include <glm/detail/type_mat4x4.hpp>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "../util/geometry.h"

Renderer::Renderer(int width, int height, StaticShader *shader) : m_width(width), m_height(height), m_projectionMatrix(glm::mat4(0.0f)), m_shader(shader) {
    m_projectionMatrix = createProjectionMatrix(width, height);
}

void Renderer::prepare() const {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::init() const {
    debug(glEnable(GL_DEPTH_TEST));
    debug(glEnable(GL_BLEND));
    debug(glEnable(GL_CULL_FACE));
    debug(glCullFace(GL_BACK));
    debug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::render(const std::map<const TexturedModel*, std::list<Entity*> > &entities) const {
    m_shader->loadProjectionMatrix(m_projectionMatrix);

    for (auto it = entities.begin(); it != entities.end(); it++) {
        const TexturedModel &model = *(it->first);
        model.bind();
        const Texture &texture = model.getTexture();
        m_shader->loadSpecular(texture.getShineDamper(), texture.getReflectivity());

        std::list<Entity*> list = it->second;
        for (auto e = list.begin(); e != list.end(); e++) {
            prepareInstance(**e);
            debug(glDrawElements(GL_TRIANGLES, model.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));
        }

        model.unbind();
    }
}

void Renderer::prepareInstance(const Entity &entity) const {
    glm::mat4 transformationMatrix = createTransformationMatrix(entity.getPos(),
                                                                entity.getRotation(),
                                                                entity.getScale());
    m_shader->loadTransformationMatrix(transformationMatrix);
}
