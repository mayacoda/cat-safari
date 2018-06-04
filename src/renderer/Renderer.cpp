
#include "Renderer.h"

void Renderer::prepare() const {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    va.bind();
    ib.bind();
    shader.bind();

    debug(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::render(const Model &model) const {
    model.getVertexArray().bind();
    model.getIndexBuffer().bind();
    model.getShader().bind();

    debug(glDrawElements(GL_TRIANGLES, model.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::init() const {
    debug(glEnable(GL_BLEND));
    debug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}
