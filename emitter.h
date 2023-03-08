#include <rendering/window.h>

class Emitter {
public:
    glm::vec2 position = {-0.5, 0};
    float spread = 0.1;
    float angle = 0;
    float velocity = 0.1;
    float pps = 2;
    float particleSize = 5;
    float elapsed = 0;

    void setPosition(glm::vec2 position) { this->position = position; }

    void setSpread(float spread) { this->spread = spread; }
};

class Explosion : public Emitter {
public:
    Explosion(float spread, glm::vec2 position) {
        setPosition(position);
        setSpread(spread);
    };
};