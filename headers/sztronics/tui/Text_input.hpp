#pragma once

#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/tui/Text.hpp>
#include <sztronics/miscellaneous/Misc_functions.hpp>

/// @brief Dynamic text that can be appended via input.
class Text_input : public Text
{
    public:
    Text_input(Vector2i size_limit = {0, 0}, Vector2i position = {0, 0},
                TUI::Color foreground = TUI::WHITE, TUI::Color background = TUI::TRANSPARENT);

    Text_input& operator= (const Text_input& other) = default;

    protected:
    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};