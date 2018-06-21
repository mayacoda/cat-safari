
#include "GUIRenderer.h"

GUIRenderer::GUIRenderer() {
    m_shader = new GUIShader();

    float        positions[8] = {-1, 1, -1, -1, 1, 1, 1, -1}; // positions of the quad on the screen
    unsigned int indices[6]   = {0, 1, 2, 1, 3, 2};

    auto* va = new VertexArray();
    auto* vb = new VertexBuffer(positions, sizeof(float) * 8);
    BufferLayout layout;
    layout.pushFloat(2, "position");
    va->addBuffer(*vb, layout);

    auto* ib = new IndexBuffer(indices, 6);
    m_quad = new Model(va, ib);

}

void GUIRenderer::render(std::vector<GUITexture*> textures) const {
    m_quad->bind();
    m_shader->bind();

    for (auto it = textures.begin(); it != textures.end(); it++) {
        GUITexture* gui = *it;
        Texture* tex = gui->getTexture();

        tex->bind();
        glDrawElements(GL_TRIANGLES, m_quad->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
        tex->unbind();
    }

    m_shader->unbind();
    m_quad->unbind();
}

GUIRenderer::~GUIRenderer() {
    delete m_quad;
    delete m_shader;
}
