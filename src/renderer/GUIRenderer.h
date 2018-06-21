
#ifndef SAFARI_GUIRENDERER_H
#define SAFARI_GUIRENDERER_H


#include <glm/vec2.hpp>
#include "../shaders/GUIShader.h"
#include "../models/Model.h"
#include "../texture/GUITexture.h"

class GUIRenderer {
private:
    GUIShader* m_shader;
    Model* m_quad;

public:
    GUIRenderer();

    virtual ~GUIRenderer();

    void render(std::vector<GUITexture*> textures) const;
};


#endif //SAFARI_GUIRENDERER_H
