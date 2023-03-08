#include <rendering/window.h>
#pragma once

class Force {
public:
    glm::vec2 position = {0, 0};
    float force = (float)0.001;
};

class BlackHole : public Force {
public:
    glm::vec2 position = {0, 0};
    float force = (float)0.01;
};

class DistantStar : public Force {
public:
    glm::vec2 position = {0, 0};
    float force = (float)0.0000001;
};