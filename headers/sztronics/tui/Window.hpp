#pragma once

#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>

/// @brief Used to align objects relative to window borders
class Window : public TUI::UI_Object {
    public:
    TUI::Glyph fill;

    Vector2i get_size() const override {
        return screen_size;
    }
    private:

    Vector2i screen_size = {0, 0};
    void draw_self(TUI& tui, unsigned input, Vector2i origin) override {
        screen_size = tui.get_screen_size();
        if (fill.background != TUI::Color::TRANSPARENT || 
            (fill.foreground != TUI::Color::TRANSPARENT && fill.symbol != ' ')) {
            for (int x = 0; x < screen_size.x; x++) {
                for (int y = 0; x < screen_size.y; y++) {
                    tui.draw_glyph({x, y}, fill);
                }
            }
        }
    }
};