#pragma once

#include <sztronics/miscellaneous/Vector2i.hpp>
#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/tui/Rect.hpp>
#include <sztronics/tui/Text.hpp>
#include <sztronics/miscellaneous/Timer.hpp>

#include <string>
#include <vector>
#include <queue>
#include <functional>

/// @brief Base animated class. Changes its state on tick.
class Animated : public TUI::UI_Object
{
    public:
    Animated(float period);
    
    /// @brief If paused, the object is still visible but the animation does not play.
    bool paused = false;

    inline float get_period() { return timer.events.back().t_seconds;}
    inline void set_period(float period) { timer.events.back().t_seconds = period;}

    /// @brief Specify what the animated object does when its frame changes
    virtual void tick() = 0;

    protected:
    Timer timer;
    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};

/// @brief Object that toggles its children' visibility once in a period.
class Blinker : public Animated
{
    public:
    Blinker(float period = 0.5);
    
    protected:
    void tick() override;
};

/// @brief Box with text moving along its contour. CRAZY!
class Crazy_box : public Animated
{
    public:
    Crazy_box(float period = 0.1);
    std::string text;
    TUI::Color text_color = TUI::BLACK;
    Rect rect;

    Vector2i get_size() const override;

    protected:
    int offset = 0;

    void tick() override;
    Vector2i position_character(int position);
    void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};

/// @brief Text that appears dynamically as if it was being typed
class Rolling_text : public Animated
{
    public:
    Rolling_text(float period = 0.1);
    std::string origin_text;
    Text text;

    Vector2i get_size() const override;

    protected:

    int n_drawn_chars = 0;
    void tick() override;
    void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) override;
};