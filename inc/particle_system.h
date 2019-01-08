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
    virtual void draw(RenderTarget& target, RenderStates states) const override;
    void init(int count);
    void emit_particles(const Vector2f& position);
    void update(float dt_as_seconds);
    bool running();

  private:
    Particles particles_;
    VertexArray vertices_;
    float duration_{};
    bool is_running_{false};
};

} // namespace game
