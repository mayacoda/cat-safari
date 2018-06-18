#ifndef SAFARI_HELPERS_H
#define SAFARI_HELPERS_H

#include <cstdlib>

inline int iRandomRange(int min, int max) {
    int random = rand() % (max) + min;
    return random;
}


inline float fRandomRange(float min, float max) {

    float r3 = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    return r3;
}


#endif //SAFARI_HELPERS_H
