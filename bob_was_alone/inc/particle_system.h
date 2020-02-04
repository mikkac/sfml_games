#pragma once
#include "particle.h"
#include <vector>

namespace game
{
using namespace sf;

class ParticleSystem : public Drawable
{
    using Particles = std::vector<Particle>;

  public:
    ParticleSystem() = default;
    void init(unsigned num_particles);
    void update(float dt_as_seconds);
    void emit_particles(const Vector2f& start_pos);
    virtual void draw(RenderTarget& target, RenderStates states) const override { target.draw(vertices_, states); }
    bool running() { return is_running_; }

  private:
    Particles particles_;
    VertexArray vertices_;
    float duration_{};
    bool is_running_{false};
};

} // namespace game
