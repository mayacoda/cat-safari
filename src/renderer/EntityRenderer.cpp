
#include <glm/detail/type_mat4x4.hpp>
#include <glm/glm.hpp>
#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4 matrix) : m_shader(shader) {

    m_shader->bind();
    m_shader->loadProjectionMatrix(matrix);
    m_shader->unbind();
}

void EntityRenderer::render(const std::map<const TexturedModel*, std::list<Entity*> > &entities) const {

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

void EntityRenderer::prepareInstance(const Entity &entity) const {
    glm::mat4 transformationMatrix = createTransformationMatrix(entity.getPos(),
                                                                entity.getRotation(),
                                                                entity.getScale());
    m_shader->loadTransformationMatrix(transformationMatrix);
}
