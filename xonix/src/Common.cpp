#include "Arduino.h"

int GetRandomDirection()
{
    if (random(0, 2) > 0) return random(1, 3);
    return -random(1, 3);
}