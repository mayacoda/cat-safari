
#ifndef SAFARI_GAMEWORLD_H
#define SAFARI_GAMEWORLD_H


#include "../renderer/MasterRenderer.h"
#include <GLFW/glfw3.h>

class GameWorld {

private:
    MasterRenderer* m_master;
    Camera        * m_camera;
    Light         * m_light;
    StaticShader  * m_shader;

    GLFWwindow* m_window;

    std::vector<Entity*> m_entities;

    glm::dvec2 m_mousePos;

public:

    virtual ~GameWorld();

    void init(GLFWwindow* window);

    void update(double deltaTime);

    void render() const;

    void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // coordinates relative to top left corner of window client area
    void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);

    // vertical scroll is the y offset
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};


#endif //SAFARI_GAMEWORLD_H
