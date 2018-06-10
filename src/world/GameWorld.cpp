
#include <glm/glm.hpp>
#include "../util/fileUtil.h"
#include "GameWorld.h"

GameWorld::~GameWorld() {
    m_master->cleanUp();

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        delete *it;
    }

    delete m_master;
    delete m_camera;
    delete m_light;
}

void GameWorld::init(GLFWwindow* window) {
    m_window = window;
    m_camera = new Camera(glm::vec3(0, 10, -30), 0, 180, 0);
    m_shader = new StaticShader("basic", "basic");
    m_light  = new Light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    Renderer renderer(width, height, m_shader);
    renderer.init();

    glfwGetCursorPos(m_window, &m_mousePos.x, &m_mousePos.y);

    m_master = new MasterRenderer(*m_shader, renderer);

    TexturedModel* flare = loadObjModel("stall");

    Entity* entityFromFile  = new Entity(*flare);
    Entity* entityFromFile1 = new Entity(*flare);
    entityFromFile1->increasePosition(2, 0, 0);
    Entity* entityFromFile2 = new Entity(*flare);
    entityFromFile2->increasePosition(0, 2, 0);
    Entity* entityFromFile3 = new Entity(*flare);
    entityFromFile3->increasePosition(0, 0, 2);

    m_entities.push_back(entityFromFile);
    m_entities.push_back(entityFromFile1);
    m_entities.push_back(entityFromFile2);
    m_entities.push_back(entityFromFile3);
}


void GameWorld::update(double deltaTime) {

}

void GameWorld::render() const {

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        m_master->processEntity(*it);
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

    double camX, camY, camZ, yaw, pitch, roll;

    if (isPressed) {
        switch (key) {
            case GLFW_KEY_UP:
                camY += 0.5;
                yaw   = 0.5f;
                break;
            case GLFW_KEY_DOWN:
                camY -= 0.5;
                yaw   = -0.5f;
                break;
            case GLFW_KEY_LEFT:
                camX -= 0.5;
                pitch = -0.5f;
                break;
            case GLFW_KEY_RIGHT:
                camX += 0.5;
                pitch = 0.5f;
                break;
            case GLFW_KEY_S:
                camZ += 0.5;
                roll  = 0.5f;
                break;
            case GLFW_KEY_W:
                camZ -= 0.05;
                roll  = -0.5f;
                break;
        }

    }
}

void GameWorld::mousePositionCallback(GLFWwindow* window, double xPos, double yPos) {

    double yawDiff = m_mousePos.x - xPos;
    double pitchDiff = m_mousePos.y - yPos;

    m_mousePos = glm::dvec2(xPos, yPos);

    m_camera->rotate(glm::vec3(pitchDiff * .1, yawDiff * .1, 0));
}

void GameWorld::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    if (yOffset > 0) {
        m_camera->moveToward(glm::vec3(0,0,0), 1);
    } else {
        m_camera->moveToward(glm::vec3(0,0,0), -1);
    }
}
