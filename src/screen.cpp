#include "screen.h"
#include "utils.h"
namespace game
{
Screen::Screen(const Vector2u& res, const std::string& title)
    : window{VideoMode(res.x, res.y), title, Style::Fullscreen},
      resolution{res}, main_view{FloatRect(0, 0, res.x, res.y)} {
    crosshair.setTexture(holder.get_texture("res/graphics/crosshair070.png"));
    crosshair.setOrigin(32.f, 32.f);
}
} // namespace game