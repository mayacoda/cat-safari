
#ifndef SAFARI_RENDERER_H
#define SAFARI_RENDERER_H


#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../models/Model.h"
#include "../world/Entity.h"
#include "../world/Camera.h"

class Renderer {
private:
    int m_width, m_height;

    glm::mat4 m_projectionMatrix;

public:

    Renderer(int width, int height);

    void init() const;

    void prepare() const;

    void render(const VertexArray &va, const IndexBuffer &ib, Shader &shader) const;

    void render(const Entity &entity, Shader &shader, Camera &camera) const;
};


#endif //SAFARI_RENDERER_H
