
#ifndef SAFARI_LIGHT_H
#define SAFARI_LIGHT_H

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Light {
private:
    glm::vec3 m_pos;
    glm::vec3 m_color;
public:
    Light(const glm::vec3 &m_pos, const glm::vec3 &m_color);

    const glm::vec3 &getPos() const;

    const glm::vec3 &getColor() const;

};


#endif //SAFARI_LIGHT_H
