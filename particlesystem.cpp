#include <particlesystem/particlesystem.h>
#include <particlesystem/particle.h>
//#include <particlesystem/emitter.h>
#include <particlesystem/force.h>
#include <particlesystem/info.h>
#include <rendering/window.h>
#pragma once




using namespace std;

namespace {
constexpr float Pi = 3.141592654f;
const float Tau = 2.f * Pi;
}  // namespace

void Particlesystem::createParticles(Emitter& E, float dt) {
    float size = (float)particles.size();

    if (size >= maxParticles) {
       
    } else {
        E.elapsed = E.elapsed + dt;

        if (E.elapsed >= (1 / E.pps)) {
            int amount = (int)(E.elapsed / (1 / E.pps));
            while (amount) {
                Particle p;
                p.position = E.position;

                double s1 = (rand() % 100 * ((double)E.spread * (double)2)) / (double)100;
                s1 = s1 - E.spread;

                float x = cos(E.angle + (float)s1);
                float y = sin(E.angle + (float)s1);

                p.velocity = {x * E.velocity, y * E.velocity};

                p.radius = E.particleSize;
                particles.push_back(p);
                amount = amount - 1;
            }
            E.elapsed = 0;
        }
    }
}

void Particlesystem::update(vector<Force> forces, float dt) {
    
  
    if (particles.size() > 0) {
        // For each particle
        for (int i = 0; i < (int)particles.size(); i++) {

            particles[i].lifetime = particles[i].lifetime - dt;

            if (particles[i].lifetime < 0) {
                particles.erase(particles.begin() + i);
            } else {
                // Calculate force
                // Calculate new position and velocity
                for (int j = 0; j < forces.size(); j++) {
                    float dx = forces[j].position.x - (particles[i].position.x);
                    float dy = forces[j].position.y - (particles[i].position.y);

                    float dis = sqrt(dx * dx + dy * dy);

                    if (dis < 0.5) {
                        if (dx != 0) {
                            // particles[i].velocity.x += 0.001 * forces[j].force * sign(dx) *
                            // pow(abs(dx), 0.5);
                            particles[i].velocity.x += 0.002 * forces[j].force * dx;
                        } else {
                            particles[i].velocity.x += 0.002 * forces[j].force * 0;
                        }
                        if (dy != 0) {
                            // particles[i].velocity.y += 0.001 * forces[j].force * sign(dy) *
                            // pow(abs(dy), 0.5);
                            particles[i].velocity.y += 0.002 * forces[j].force * dy;
                        } else {
                            particles[i].velocity.y += 0.002 * forces[j].force * 0;
                        }
                    } else if (dis < 1) {
                        if (dx != 0) {
                            // particles[i].velocity.x += 0.001 * forces[j].force * sign(dx) *
                            // pow(abs(dx), 0.5);
                            particles[i].velocity.x += 0.001 * forces[j].force * dx;
                        } else {
                            particles[i].velocity.x += 0.001 * forces[j].force * 0;
                        }
                        if (dy != 0) {
                            // particles[i].velocity.y += 0.001 * forces[j].force * sign(dy) *
                            // pow(abs(dy), 0.5);
                            particles[i].velocity.y += 0.001 * forces[j].force * dy;
                        } else {
                            particles[i].velocity.y += 0.001 * forces[j].force * 0;
                        }
                    }
                }
                particles[i].position.x += particles[i].velocity.x * dt;
                particles[i].position.y += particles[i].velocity.y * dt;
            }
        }
    }
}

