
#include <glm/detail/type_mat4x4.hpp>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "../util/geometry.h"

void Renderer::prepare() const {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Entity &entity, Shader &shader, Camera &camera, Light &light) const {
    const Model &model = entity.getModel();
    model.render();
    shader.bind();


    glm::mat4 transformationMatrix = createTransformationMatrix(entity.getPos(),
                                                                entity.getRotation(),
                                                                entity.getScale());

//    glm::mat4 viewMatrix           = createViewMatrix(camera);
    glm::mat4 viewMatrix           = createViewMatrix(camera.getPos());

    shader.setUniformMatrix4("u_transformationMatrix", transformationMatrix);
    shader.setUniformMatrix4("u_projectionMatrix", m_projectionMatrix);
    shader.setUniformMatrix4("u_viewMatrix", viewMatrix);
    shader.setUniform3f("u_lightPosition", light.getPos());
    shader.setUniform3f("u_lightColor", light.getColor());

    debug(glDrawElements(GL_TRIANGLES, model.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::init() const {
    debug(glEnable(GL_DEPTH_TEST));
    debug(glEnable(GL_BLEND));
    debug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Renderer::Renderer(int width, int height) : m_width(width), m_height(height), m_projectionMatrix(glm::mat4(0.0f)) {
    m_projectionMatrix = createProjectionMatrix(width, height);
}
