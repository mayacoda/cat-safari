
#include <glm/glm.hpp>
#include "../util/fileUtil.h"
#include "GameWorld.h"

GameWorld::~GameWorld() {
    m_master->cleanUp();

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        delete *it; // doesn't delete the model because the model doesn't belong to it
    }

    for (auto it = m_models.begin(); it != m_models.end(); it++) {
        delete *it;
    }

    for (auto it = m_terrains.begin(); it != m_terrains.end(); it++) {
        delete *it;
    }

    delete m_master;
    delete m_camera;
    delete m_light;
}

void GameWorld::init(GLFWwindow* window) {
    m_window = window;
    m_camera = new Camera(glm::vec3(0, 10, -30), 0, 180, 0);
    m_light  = new Light(glm::vec3(0, 100, -20), glm::vec3(1, 1, 1));

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    glfwGetCursorPos(m_window, &m_mousePos.x, &m_mousePos.y);

    m_master = new MasterRenderer(width, height);

    TexturedModel* flare = loadObjModel("stall");

    Entity* entityFromFile  = new Entity(flare);
    Entity* entityFromFile1 = new Entity(flare);
    entityFromFile1->increasePosition(20, 0, 0);
    Entity* entityFromFile2 = new Entity(flare);
    entityFromFile2->increasePosition(0, 0, 0);
    Entity* entityFromFile3 = new Entity(flare);
    entityFromFile3->increasePosition(0, 0, 20);

    m_entities.push_back(entityFromFile);
    m_entities.push_back(entityFromFile1);
    m_entities.push_back(entityFromFile2);
    m_entities.push_back(entityFromFile3);

    m_models.push_back(flare);

    m_terrains.push_back(new Terrain(0, 0));
    m_terrains.push_back(new Terrain(1, 0));
    m_terrains.push_back(new Terrain(-1, 0));
    m_terrains.push_back(new Terrain(0, 1));
    m_terrains.push_back(new Terrain(1, 1));
    m_terrains.push_back(new Terrain(-1, 1));
    m_terrains.push_back(new Terrain(0, -1));
    m_terrains.push_back(new Terrain(1, -1));
    m_terrains.push_back(new Terrain(-1, -1));
}

void GameWorld::update(double deltaTime) {

}

void GameWorld::render() const {

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        m_master->processEntity(*it);
    }

    for (auto it = m_terrains.begin(); it != m_terrains.end(); it++) {
        m_master->processTerrain(*it);
    }

    m_master->render(*m_light, *m_camera);
}

void GameWorld::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static bool isPressed = false;

    if (action == GLFW_PRESS) {
        isPressed = true;
    } else if (action == GLFW_RELEASE) {
        isPressed = false;
    }

    float camX = 0, camZ = 0;

    if (isPressed) {
        switch (key) {
            case GLFW_KEY_W:
                camZ += 1;
                break;
            case GLFW_KEY_S:
                camZ -= 1;
                break;
            case GLFW_KEY_A:
                camX += 1;
                break;
            case GLFW_KEY_D:
                camX -= 1;
                break;
            default:break;
        }

        m_camera->moveBy(glm::vec3(camX, 0, camZ));
    }
}

void GameWorld::mousePositionCallback(GLFWwindow* window, double xPos, double yPos) {

    int height, width;
    glfwGetWindowSize(window, &width, &height);

    double yaw = width / 2. - xPos;
    double pitch = height / 2. - yPos;

    m_camera->rotate(glm::vec3(pitch * .1, 180 + yaw * .1, 0));
}

void GameWorld::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

    if (yOffset > 0) {
        m_camera->moveToward(glm::vec3(0, 0, 0), 1);
    } else {
        m_camera->moveToward(glm::vec3(0, 0, 0), -1);
    }
}
