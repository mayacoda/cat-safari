
#ifndef SAFARI_COLLISIONS_H
#define SAFARI_COLLISIONS_H


#include "../models/Model.h"

class Collisions {
public:
    static bool isHit(const BoundingBox &target,
                      const glm::mat4 &targetTransform,
                      const BoundingBox &dest,
                      const glm::mat4 &destTransform);
};


#endif //SAFARI_COLLISIONS_H
