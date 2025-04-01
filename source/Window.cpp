#include <sztronics/tui/Window.hpp>

void Window::draw_self(TUI& tui, unsigned input, Vector2i origin) {
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