#include <sztronics/tui/Text_input.hpp>

Text_input::Text_input(Vector2i size_limit, Vector2i position,
                       TUI::Color foreground, TUI::Color background) :
                       Text("", size_limit, position, foreground, background) {}
