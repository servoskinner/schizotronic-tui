#pragma once

#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/miscellaneous/Misc_functions.hpp>

/// @brief Basic non-interactive text.
class Text : public TUI::UI_Object
{
    public:
    Text(std::string text = "", Vector2i constraints = {0, 0}, Vector2i position = {0, 0}, 
         TUI::Color foreground = TUI::WHITE, TUI::Color background = TUI::TRANSPARENT);

    Text& operator= (const Text& other) = default;

    TUI::Color background = TUI::TRANSPARENT;
    TUI::Color foreground = TUI::WHITE;
    
    /// @brief If enabled, treats text as a whole box instead of fitting minimum size.
    bool fill_max_size = false;

    Vector2i get_size() const override;
    void set_xylimit(Vector2i xy_lim);

    void set_xlimit(int x_lim);
    void set_ylimit(int y_lim);

    void set_text(std::string new_text);
    void set_wrap(bool value);

    inline std::string get_text() const { return raw_text; }
    inline bool get_wrap() const { return wrap; }

    protected:
    /// @brief If enabled, wraps text carefully so it is fully visible. If not, does not add newlines
    bool wrap = true;
    /// @brief Max width and height in chars
    Vector2i constraints;
    std::string raw_text;
    std::vector<std::string> text_lines;
    /// @brief regenerate text_lines when either size constraints or text content have been changed
    virtual void refit_text();

    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};