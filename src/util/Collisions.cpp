
#include "Collisions.h"
#include <glm/glm.hpp>

bool Collisions::isHit(const BoundingBox &target, const glm::mat4 &targetTransform, const BoundingBox &dest, const glm::mat4 &destTransform) {
    auto targetTrans = target.transformPoints(targetTransform);
    auto destTrans = dest.transformPoints(destTransform);

    Hexahedron hex;
    hex.createFromBBPoints(destTrans);
    // go through points of target
    for (auto i = targetTrans.begin(); i != targetTrans.end(); ++i) {
        // if any point is inside, return true
        if (hex.isInside(*i)) {
            return true;
        }
    }

    // if no point returned true, return false
    return false;
}
