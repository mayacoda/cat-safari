
#ifndef SAFARI_RENDERER_H
#define SAFARI_RENDERER_H


#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <list>
#include <map>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../models/Model.h"
#include "../world/Entity.h"
#include "../world/Camera.h"
#include "../world/Light.h"
#include "../shaders/StaticShader.h"
#include "../util/geometry.h"

class Renderer {
private:
    int m_width, m_height;

    glm::mat4 m_projectionMatrix;

    StaticShader m_shader;

    void prepareInstance(const Entity &entity) const {
        glm::mat4 transformationMatrix = createTransformationMatrix(entity.getPos(),
                                                                    entity.getRotation(),
                                                                    entity.getScale());
        m_shader.loadTransformationMatrix(transformationMatrix);
    }

public:

    Renderer(int width, int height, const StaticShader &shader);

    void init() const;

    void prepare() const;

    void render(const std::map<const TexturedModel*, std::list<Entity*> > &entities) const;

};


#endif //SAFARI_RENDERER_H
