
#include "TerrainRenderer.h"

void TerrainRenderer::loadModelMatrix(Terrain* terrain) const {
    glm::mat4 transformationMatrix = createTransformationMatrix(glm::vec3(terrain->getX(), 0, terrain->getZ()),
                                                                glm::vec3(0), 1);
    m_shader->loadTransformationMatrix(transformationMatrix);
}

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4 matrix) : m_shader(shader) {
    m_shader->bind();
    m_shader->loadProjectionMatrix(matrix);
    m_shader->unbind();
}

void TerrainRenderer::render(std::list<Terrain*> terrains) const {
    for (auto it = terrains.begin(); it != terrains.end(); it++) {
        Terrain* terrain = *it;

        TexturedModel* model = terrain->getModel();
        model->bind();
        const Texture &texture = model->getTexture();
        texture.bind();
        m_shader->loadSpecular(texture.getShineDamper(), texture.getReflectivity());

        loadModelMatrix(terrain);
        debug(glDrawElements(GL_TRIANGLES, model->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));

        model->unbind();
    }
}
