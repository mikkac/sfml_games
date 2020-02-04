#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

namespace game
{
struct Screen {
    Screen(const Vector2u& res, const std::string& title);
    void set_main_view() { window.setView(main_view); }
    void set_hud_view() { window.setView(hud_view); }
    RenderWindow window;
    Vector2u resolution;
    View main_view;
    View hud_view;
    Sprite crosshair;
};
} // namespace game
