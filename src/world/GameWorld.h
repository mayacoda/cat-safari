
#ifndef SAFARI_GAMEWORLD_H
#define SAFARI_GAMEWORLD_H


#include "../renderer/MasterRenderer.h"
#include "Player.h"
#include "GUI.h"
#include "GameState.h"
#include <GLFW/glfw3.h>
#include <set>

class GameWorld {

private:
    MasterRenderer* m_master;
    Camera        * m_camera;
    Light         * m_light;
    Player        * m_player;
    GUI           * m_gui;

    GLFWwindow* m_window;

    GameState* m_state;

    std::vector<Entity*>  m_entities;
    std::vector<Entity*>  m_cats;
    std::vector<Terrain*> m_terrains;
    std::vector<Model*>   m_models; // to keep track of models created so they can be deleted

    std::set<int> m_photographed;

    mutable int m_objectsDrawn;

    void pollKeyboard() const;

    void pollMouse() const;

    bool isCatOnScreen();

public:

    virtual ~GameWorld();

    void init(GLFWwindow* window, GameState* state);

    void update(double deltaTime);

    void render() const;

    // vertical scroll is the y offset
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    void mouseButtonCallback(GLFWwindow* window, int button, int action);
};


#endif //SAFARI_GAMEWORLD_H
