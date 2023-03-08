#pragma once
#include <rendering/window.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

class Particle {


public:

	glm::vec2 position = {0, 0};
    glm::vec2 velocity = {0, 0};
    glm::vec2 acceleration = {0, 0};
    glm::vec4 color = {1.0f, 0.5f, 0.31f, 1};
    float lifetime = (float)60; 
    float radius = (float)1;

};