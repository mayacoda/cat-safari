
#ifndef SAFARI_UI_H
#define SAFARI_UI_H


#include <vector>
#include "../texture/GUITexture.h"

class GUI {
private:
    bool m_isPhotoView;
    mutable std::vector<GUITexture*> m_textures;

    GUITexture* m_crosshairs;
public:
    GUI() {
        m_crosshairs = new GUITexture(glm::vec2(0), new Texture("./res/textures/crosshairs.png"));
    }

    const std::vector<GUITexture*> &getTextures() const {
         m_textures.clear();

        if (m_isPhotoView) {
            m_textures.push_back(m_crosshairs);
        }

        return m_textures;
    }


    void togglePhotoView() {
        m_isPhotoView = !m_isPhotoView;
    }
};


#endif //SAFARI_UI_H
