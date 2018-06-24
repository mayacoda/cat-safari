
#ifndef SAFARI_UI_H
#define SAFARI_UI_H


#include <vector>
#include "../texture/GUITexture.h"

class GUI {
private:
    bool m_isPhotoView;
    bool m_isPhotoSuccess;
    bool m_isPhotoFailure;
    mutable std::vector<GUITexture*> m_textures;

    float m_timer;

    GUITexture* m_crosshairs;
    GUITexture* m_success;
    GUITexture* m_failure;
public:
    GUI() : m_isPhotoView(false), m_isPhotoSuccess(false), m_isPhotoFailure(false), m_timer(0) {
        m_crosshairs = new GUITexture(glm::vec2(0), new Texture("./res/textures/crosshairs.png"));
        m_success = new GUITexture(glm::vec2(0), new Texture("./res/textures/success.png"));
        m_failure = new GUITexture(glm::vec2(0), new Texture("./res/textures/failure.png"));
    }

    void update(float dt) {
        if (m_timer > 0) {
            m_timer -= dt;
        } else if (m_isPhotoFailure || m_isPhotoSuccess) {
            clearState();
        }
    }

    const std::vector<GUITexture*> &getTextures() const {
         m_textures.clear();

        if (m_isPhotoSuccess) {
            m_textures.push_back(m_success);
        }

        if (m_isPhotoFailure) {
            m_textures.push_back(m_failure);
        }

        if (m_isPhotoView) {
            m_textures.push_back(m_crosshairs);
        }

        return m_textures;
    }

    void togglePhotoView() {
        m_isPhotoView = !m_isPhotoView;
    }

    void isSuccess(bool success) {
        m_isPhotoSuccess = success;
        m_isPhotoFailure = !success;
        m_timer = 1;
    }

    void clearState() {
        m_isPhotoSuccess = false;
        m_isPhotoFailure = false;
    }
};


#endif //SAFARI_UI_H
