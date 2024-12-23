#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include "globals.h"


/*
   Генерация случайного float в диапазоне [from; to].
*/
float rand_from_to(float from, float to) {
    float fraction = (float)std::rand() / (float)RAND_MAX;
    return from + fraction * (to - from);
}

/*
   Генерация случайного float в диапазоне [0; to].
*/
float rand_up_to(float to) {
    return rand_from_to(0.0f, to);
}

#endif // UTILITIES_H
