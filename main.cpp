#include <tracy/Tracy.hpp>
#include <rendering/window.h>
#include <particlesystem/particlesystem.h>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <fmt/format.h>

// Simple random functions to get started
// Random float (0,1)
float rnd() { return rand() / static_cast<float>(RAND_MAX); }

// Random float (-1,1)
float srnd() { return rnd() * 2.0f - 1.0f; }

int main(int, char**) try {
    rendering::Window window("Particle System v0.0.1 pre-release alpha", 850, 850);


    // Containers to store information about each particle to draw.
    std::vector<glm::vec2> positions;
    std::vector<float> sizes;
    std::vector<glm::vec4> colors;

    std::vector<Emitter> emitters;
    std::vector<Force> forces;

    Emitter E1;
    E1.position = {-0.5, 0.2};

    emitters.push_back(E1);

    Explosion Ex1(3, glm::vec2{0.5, 0});

    emitters.push_back(Ex1);

    Force F1;
    F1.position = {-0.6, 0};
    F1.force = 1;
    forces.push_back(F1);

  /*  Force F2;
    F2.position = {0.5, 0.5};
    F2.force = 1;
    forces.push_back(F2);*/


    double prevTime = 0.0;
    float speed = 1.0f;
    bool running = true;

     Particlesystem ps;
   
    while (running) {
        window.beginFrame();

        const double t = window.time();
        const double dt = t - prevTime;
        prevTime = t;



        // Create some global smooth rocking motion
        const glm::vec2 vel =
            glm::vec2{static_cast<float>(std::cos(t)), -static_cast<float>(std::abs(std::sin(t)))} *
            0.2f;

        for (int i = 0; i < emitters.size(); i++) {
            ps.createParticles(emitters[i], dt);
        }



        {
            ZoneScopedN("Update particles");

               for (int i = 0; i < ps.particles.size(); i++) {

                Particle& currentParticle = ps.particles[i];
                positions.push_back(currentParticle.position);
                sizes.push_back(currentParticle.radius);
                colors.push_back(currentParticle.color);
                }

                ps.update(forces, dt);

            // Simulation dt may differ from actual dt based on the simulation speed
            const float sim_dt = static_cast<float>(dt) * speed;

            //copydt = static_cast<float>(dt) * speed;

        }

        // Clear screen with color
        window.clear({0, 0, 0, 1});

        // Draw particles
        window.drawPoints(positions, sizes, colors);

        // UI
        {
            window.beginGuiWindow("UI");
            window.text("I'm text!");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            window.sliderFloat("Angle E1", emitters[0].angle, 0.001f, 6.2831f);
            window.sliderFloat("Spread E1", emitters[0].spread, 0.001f, 6.2831f);
            window.sliderFloat("Particles/s E1", emitters[0].pps, 0.1f, 10.0f);
            window.sliderFloat("Velocity E1", emitters[0].velocity, 0.1f, 1.0f);

            window.sliderFloat("Force F1", forces[0].force, 1.0f, 10.0f);

            window.sliderFloat("Max particles", ps.maxParticles, 10, 10000);

            // ui::sliderFloat("Speed", speed, 0.01f, 10.0f);
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }

        window.endFrame();
        running = running && !window.shouldClose();
    }

    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
