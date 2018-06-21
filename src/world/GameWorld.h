
#ifndef SAFARI_GAMEWORLD_H
#define SAFARI_GAMEWORLD_H


#include "../renderer/MasterRenderer.h"
#include "Player.h"
#include "GUI.h"
#include <GLFW/glfw3.h>

class GameWorld {

private:
    MasterRenderer* m_master;
    Camera        * m_camera;
    Light         * m_light;
    Player        * m_player;
    GUI           * m_gui;

    GLFWwindow* m_window;

    std::vector<Entity*>  m_entities;
    std::vector<Terrain*> m_terrains;
    std::vector<Model*>   m_models; // to keep track of models created so they can be deleted

    void pollKeyboard() const;

    void pollMouse() const;

public:

    virtual ~GameWorld();

    void init(GLFWwindow* window);

    void update(double deltaTime);

    void render() const;

    // vertical scroll is the y offset
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};


#endif //SAFARI_GAMEWORLD_H
