#include "particle_system.h"
#include "random.h"
#include <cmath>

namespace game
{
namespace
{ // anonymous
Random rand;
} // namespace

void ParticleSystem::init(unsigned num_particles) {
    vertices_.setPrimitiveType(Points);
    vertices_.resize(num_particles);

    for (unsigned i = 0; i < num_particles; ++i) {
        float angle = rand(360) * 3.14f / 180.f;
        float speed = rand(600) + 600.f;

        Vector2f velocity{static_cast<float>(cos(angle) * speed), static_cast<float>(sin(angle) * speed)};
        particles_.push_back(Particle(velocity));
    }
}

void ParticleSystem::update(float dt_as_seconds) {
    duration_ -= dt_as_seconds;
    int current_vertex{0};
    for (auto& particle : particles_) {
        particle.update(dt_as_seconds);
        vertices_[current_vertex++].position = particle.get_position();
    }
    if (duration_ < 0) is_running_ = false;
}

void ParticleSystem::emit_particles(const Vector2f& start_pos) {
    is_running_ = true;
    duration_ = 2.f;
    
    int current_vertex{0};
    for(auto& particle : particles_) {
        vertices_[current_vertex++].color = Color::Yellow;
        particle.set_position(start_pos);
    }
}

} // namespace game
