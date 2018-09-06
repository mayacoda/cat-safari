
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iomanip>
#include "../util/fileUtil.h"
#include "GameWorld.h"
#include "EntityLoader.h"
#include "../util/mouse-picking.h"

GameWorld::~GameWorld() {
    m_master->cleanUp();

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        delete *it; // doesn't delete the model because the model doesn't belong to it
    }


    for (auto it = m_cats.begin(); it != m_cats.end(); it++) {
        delete *it;
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
    delete m_gui;
}

void GameWorld::init(GLFWwindow* window, GameState* state) {
    m_window = window;
    m_light  = new Light(glm::vec3(0, 100, -20), glm::vec3(1, 1, 1));
    m_state  = state;

    m_gui = new GUI(m_state);

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    m_master = new MasterRenderer(width, height);

    EntityLoader::loadTerrain("./res/terrain.txt", m_entities, m_models);
    EntityLoader::loadCats(m_cats, m_entities, m_models);

    TexturedModel* player = loadObjModel("player");

    m_player = new Player(player, glm::vec3(75, 0, -40), glm::vec3(0), 1);
    m_entities.push_back(m_player);
    m_models.push_back(player);

    m_camera = new Camera(m_player, (float) width / (float) height);

    m_terrains.push_back(new Terrain(0, 0));
}

void GameWorld::update(double deltaTime) {
    pollKeyboard();
    pollMouse();

    if (m_state->getState() == GameState::play) {
        m_player->update(static_cast<float>(deltaTime), m_entities);
        m_camera->update();
        m_gui->update(static_cast<float>(deltaTime));
    }
}

void GameWorld::render() const {

    if (m_state->getState() == GameState::play) {
        m_objectsDrawn = 0;

        for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
            if (m_camera->isInView(*it)) {
                m_master->processEntity(*it);
                m_objectsDrawn++;
            }
        }

        for (auto it = m_cats.begin(); it != m_cats.end(); it++) {
            if (m_camera->isInView(*it)) {
                m_master->processEntity(*it);
                m_objectsDrawn++;
            }
        }

        std::cout << "Objects drawn " << m_objectsDrawn << std::endl;

        for (auto it = m_terrains.begin(); it != m_terrains.end(); it++) {
            m_master->processTerrain(*it);
        }

    }

    m_master->render(*m_light, *m_camera, *m_gui);
}

void GameWorld::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

    m_camera->calculateZoom(yOffset);
}

void GameWorld::pollKeyboard() const {

    GameState::STATE state = m_state->getState();

    if (state == GameState::menu) return;

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE)) {
        m_state->setState(GameState::menu);
        return;
    }

    if (glfwGetKey(m_window, GLFW_KEY_W)) {
        m_player->setSpeed(Player::MAX_SPEED);
    } else if (glfwGetKey(m_window, GLFW_KEY_S)) {
        m_player->setSpeed(-Player::MAX_SPEED);
    } else {
        m_player->setSpeed(0);
    }

    if (glfwGetKey(m_window, GLFW_KEY_A)) {
        m_player->setTurnSpeed(Player::MAX_TURN_SPEED);
    } else if (glfwGetKey(m_window, GLFW_KEY_D)) {
        m_player->setTurnSpeed(-Player::MAX_TURN_SPEED);
    } else {
        m_player->setTurnSpeed(0);
    }

    if (glfwGetKey(m_window, GLFW_KEY_SPACE)) {
        m_player->jump();
    }

    static bool wasPressed = false;
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS) {
        wasPressed = true;
    }
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_RELEASE && wasPressed) {
        wasPressed = false;
        m_master->togglePhotoView(m_camera);
        m_gui->togglePhotoView();
    }

}

void GameWorld::pollMouse() const {
    if (!(m_state->getState() == GameState::play)) return;

    double xPos, yPos;
    glfwGetCursorPos(m_window, &xPos, &yPos);

    int height, width;
    glfwGetWindowSize(m_window, &width, &height);

    if (xPos < 0 || xPos > width || yPos < 0 || yPos > height) return;

    double yaw   = width / 2. - xPos;
    double pitch = height / 2. - yPos;

    float changedPitch = Camera::DEFAULT_PITCH + ((float) pitch * 0.1f);

    if (changedPitch > 0) {
        m_camera->setPitch(changedPitch);
    }
    m_camera->setAngleAroundPlayer((float) yaw * 0.1f);
}

bool GameWorld::isCatOnScreen() {
    int       width, height;
    glm::mat4 projectionMatrix = m_master->getProjectionMatrix();
    glm::mat4 viewMatrix       = Geometry::createViewMatrix(*m_camera);
    glfwGetWindowSize(m_window, &width, &height);

    for (auto c = m_cats.begin(); c != m_cats.end(); c++) {
        Entity* cat = *c;
        if (m_photographed.find(cat->getId()) != m_photographed.end()) {
            continue;
        }
        std::vector<glm::vec3> points      = cat->getModel()->getBoundingBox().points;
        glm::mat4              modelMatrix = Geometry::createTransformationMatrix(cat->getPos(),
                                                                                  cat->getRotation(),
                                                                                  cat->getScale());

        for (auto p = points.begin(); p != points.end(); p++) {
            glm::vec2 pointOnScreen = MousePicking::worldToScreenPos(*p,
                                                                     width,
                                                                     height,
                                                                     modelMatrix,
                                                                     viewMatrix,
                                                                     projectionMatrix);

            if (pointOnScreen.x >= 0 && pointOnScreen.x <= width &&
                pointOnScreen.y >= 0 && pointOnScreen.y <= height) {
                // cat is on the screen
                int id = cat->getId();

                m_photographed.insert(id);
                if (m_photographed.size() == m_cats.size()) {
                    m_state->setState(GameState::win);
                }
                return true;
            }
        }
    }
    return false;
}

void GameWorld::mouseButtonCallback(GLFWwindow* window, int button, int action) {
    if (m_state->getState() == GameState::play &&
        button == GLFW_MOUSE_BUTTON_LEFT &&
        action == GLFW_PRESS &&
        m_camera->isInPhotoView()) {

        m_gui->isSuccess(isCatOnScreen());
    }

    if (m_state->getState() == GameState::menu && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        // clicked on new game
        if (xPos >= 313 && xPos <= 711 && yPos >= 170 && yPos <= 320) {
            m_state->setState(GameState::play);
        }

        // clicked on exit
        if (xPos >= 313 && xPos <= 711 && yPos >= 407 && yPos <= 557) {
            m_state->setState(GameState::exit);
        }
    }
}
