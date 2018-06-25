
#ifndef SAFARI_GEOMETRY_H
#define SAFARI_GEOMETRY_H

#include <glm/fwd.hpp>
#include <GL/glew.h>
#include "../world/Camera.h"

namespace Geometry {
    glm::mat4 createTransformationMatrix(glm::vec3 const &translate, glm::vec3 const &rotate, float scale);

    glm::mat4 createProjectionMatrix(int width, int height);

    glm::mat4 createPhotoViewProjectionMatrix(int width, int height);

    glm::mat4 createViewMatrix(const Camera &camera);
}


#endif //SAFARI_GEOMETRY_H
