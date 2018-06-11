
#ifndef SAFARI_RENDERER_H
#define SAFARI_RENDERER_H


#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <list>
#include <map>
#include "../models/VertexArray.h"
#include "../models/IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../models/Model.h"
#include "../world/Entity.h"
#include "../world/Camera.h"
#include "../world/Light.h"
#include "../shaders/StaticShader.h"
#include "../util/geometry.h"

class EntityRenderer {
private:
    StaticShader* m_shader;

    void prepareInstance(const Entity &entity) const;

public:

    EntityRenderer(StaticShader* shader, glm::mat4 matrix);

    void render(const std::map<const TexturedModel*, std::list<Entity*> > &entities) const;

};


#endif //SAFARI_RENDERER_H
