#include <particlesystem/particle.h>
#include <particlesystem/emitter.h>
#include <particlesystem/force.h>

class Particlesystem {
public:
    float elapsed = 0;  // seconds
    float maxParticles = 100;
    std::vector<Particle> particles;

    void createParticles(Emitter& E, float dt);

    void update(std::vector<Force> forces, float dt);
    
};