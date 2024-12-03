#include <random>
#include <SDL2/SDL.h>


const double M_PI = 3.14159265358979323846;

struct Particle {
    float x, y;
    float dx, dy;
    SDL_Color color;
    float lifetime;
    float maxLifetime;
};

std::random_device g_rd;
std::mt19937 g_gen(g_rd());

std::vector<Particle> g_particles;

// Create celebration particles
void createParticles(int centerX, int centerY) {
    // Prepare random distributions
    std::uniform_real_distribution<> angleDist(0, 2 * M_PI);
    std::uniform_real_distribution<> speedDist(1.0, 5.0);
    std::uniform_int_distribution<> colorDist(0, 255);

    // Create burst of colorful particles
    for (int i = 0; i < 200; ++i) {
        float angle = angleDist(g_gen);
        float speed = speedDist(g_gen);

        Particle p;
        p.x = centerX;
        p.y = centerY;
        p.dx = speed * cos(angle);
        p.dy = speed * sin(angle);
        
        // Random vibrant colors
        p.color = {
            static_cast<Uint8>(colorDist(g_gen)),
            static_cast<Uint8>(colorDist(g_gen)),
            static_cast<Uint8>(colorDist(g_gen)),
            255
        };

        p.lifetime = 10.0f;
        p.maxLifetime = 10.0f;
        
        g_particles.push_back(p);
    }
}

// Update particle positions and lifetimes
void updateParticles(float deltaTime) {
    for (auto it = g_particles.begin(); it != g_particles.end();) {
        it->x += it->dx;
        it->y += it->dy;
        it->lifetime -= deltaTime;
        
        if (it->lifetime <= 0) {
            it = g_particles.erase(it);
        } else {
            ++it;
        }
    }
}

// Render particles to the screen
void renderParticles(SDL_Renderer* renderer) {
    for (const auto& particle : g_particles) {
        // Fade out as lifetime decreases
        Uint8 alpha = static_cast<Uint8>(255 * (particle.lifetime / particle.maxLifetime));
        SDL_SetRenderDrawColor(renderer, 
            particle.color.r, 
            particle.color.g, 
            particle.color.b, 
            alpha);
        
        SDL_Rect particleRect = {
            static_cast<int>(particle.x), 
            static_cast<int>(particle.y), 
            3, 3
        };
        SDL_RenderFillRect(renderer, &particleRect);
    }
}

// Check if particles are still animating
bool areParticlesActive() {
    return !g_particles.empty();
}