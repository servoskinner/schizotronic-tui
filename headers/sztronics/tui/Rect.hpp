#pragma once

#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/tui/UI_Area.hpp>

/// @brief A rectangle.
class Rect : public UI_Area
{
    private: 
    const TUI::Glyph DEFAULT_LINE = {' ', TUI::TRANSPARENT, TUI::WHITE};

    public:
    Rect(Vector2i size = {0, 0}, Vector2i pos = {0, 0});
    Rect& operator= (const Rect& other) = default;

    // Corners
    TUI::Glyph tl_corner = DEFAULT_LINE, tr_corner = DEFAULT_LINE, bl_corner = DEFAULT_LINE, br_corner = DEFAULT_LINE;
    // Borders
    TUI::Glyph t_border = DEFAULT_LINE, b_border = DEFAULT_LINE, l_border = DEFAULT_LINE, r_border = DEFAULT_LINE;
    // Inside
    TUI::Glyph fill = DEFAULT_LINE;
    /// @brief Controls whether the inside part should be drawn.
    bool draw_filled = false;

    // A bunch of specific setters follow:

    inline void set_border_foreground(TUI::Color foreground) {
        tl_corner.foreground = foreground;
        tr_corner.foreground = foreground;
        bl_corner.foreground = foreground;
        br_corner.foreground = foreground;
        t_border.foreground = foreground;
        r_border.foreground = foreground;
        b_border.foreground = foreground;
        l_border.foreground = foreground;
    }

    inline void set_border_background(TUI::Color background) {
        tl_corner.background = background;
        tr_corner.background = background;
        bl_corner.background = background;
        br_corner.background = background;
        t_border.background = background;
        r_border.background = background;
        b_border.background = background;
        l_border.background = background;
    }

    inline void set_border_color(TUI::Color foreground, TUI::Color background) {
        set_border_background(background);
        set_border_foreground(foreground);
    }

    inline void set_color(TUI::Color foreground, TUI::Color background) {
        set_border_color(foreground, background);
        fill.foreground = foreground;
        fill.background = background;
    }

    inline void set_foreground(TUI::Color foreground) {
        set_border_foreground(foreground);
        fill.foreground = foreground;
    }

    inline void set_background(TUI::Color background) {
        set_border_background(background);
        fill.background = background;
    }

    inline void set_hborder(TUI::Glyph glyph) {
        t_border = glyph;
        b_border = glyph;
    }

    inline void set_vborder(TUI::Glyph glyph) {
        l_border = glyph;
        r_border = glyph;
    }

    inline void set_border(TUI::Glyph glyph) {
        set_hborder(glyph);
        set_vborder(glyph);       
    }

    inline void set_corners(TUI::Glyph glyph) {
        tl_corner = glyph;
        tr_corner = glyph;
        bl_corner = glyph;
        br_corner = glyph;
    } 

    inline void set_all(TUI::Glyph glyph) {
        set_border(glyph);
        set_corners(glyph);
        fill = glyph;
    } 

    protected:

    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};