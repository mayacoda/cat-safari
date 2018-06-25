
#include "TerrainRenderer.h"

void TerrainRenderer::loadModelMatrix(Terrain* terrain) const {
    glm::mat4 transformationMatrix = Geometry::createTransformationMatrix(glm::vec3(terrain->getX(), 0, terrain->getZ()),
                                                                glm::vec3(0), 1);
    m_shader->loadTransformationMatrix(transformationMatrix);
    m_shader->connectTextureSlots();
}

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4 matrix) : m_shader(shader) {
    m_shader->bind();
    m_shader->loadProjectionMatrix(matrix);
    m_shader->unbind();
}

void TerrainRenderer::render(std::list<Terrain*> terrains) const {
    for (auto it = terrains.begin(); it != terrains.end(); it++) {
        Terrain* terrain = *it;

        Model* model = terrain->getModel();
        model->bind();
        TerrainTexturePack* pack = terrain->getTexture();
        pack->bind();

        TerrainTexture* blendMap = terrain->getBlendMap();
        blendMap->bind(4);

        m_shader->loadSpecular(1, 0);

        loadModelMatrix(terrain);
        debug(glDrawElements(GL_TRIANGLES, model->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));

        model->unbind();
    }
}
