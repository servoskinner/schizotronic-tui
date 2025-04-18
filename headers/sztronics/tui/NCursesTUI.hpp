#pragma once

#include <ncurses.h>
#include <mutex>
#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/tui/Rect.hpp>

class NCursesTUI : public TUI
{
    public:

    /// @return Code of last key pressed
    unsigned get_input() override;

    /// @return Mouse state since last update.
    MouseState get_mouse() override;

    /// @return Terminal dimensions
    Vector2i get_screen_size() const override;

    // Mouse input control
    static void enable_mouse();
    static void disable_mouse();
    static inline bool supports_mouse() { return has_mouse(); }

    /// @return The active instance of TUI.
    static TUI& get(bool with_mouse = false);
    ~NCursesTUI() override;

    Color default_background = BLACK;

    /// @brief Makes nice ASCII line character borders for a rect.
    static void make_pretty(Rect& rect);
    
    protected:

    // It is here because NCurses is not thread-safe
    static std::mutex ncurses_mutex;
    static std::optional<std::lock_guard<std::mutex>> ncurses_mtx_lock;

    /// @brief Places given glyph at coordinates.
    void output_glyph(Vector2i pos, Glyph glyph) override;

    inline void set_color_pair(short id, short foreground, short background) { 
        init_pair(id, foreground, background);
    }

    /// @brief Maps color combinations to color pair ids.
    unsigned short get_color_code(Color foreground, Color background) const;

    unsigned last_input = 0;
    MouseState last_mouse = {};

    static bool mouse_enabled;

    void pre_render() override;
    void post_render() override;

    private:
    NCursesTUI();
};