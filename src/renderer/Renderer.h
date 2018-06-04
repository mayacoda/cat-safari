
#ifndef SAFARI_RENDERER_H
#define SAFARI_RENDERER_H


#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../models/Model.h"

class Renderer {
public:
    void init() const;

    void prepare() const;

    void render(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

    void render(const Model &model) const;
};


#endif //SAFARI_RENDERER_H
