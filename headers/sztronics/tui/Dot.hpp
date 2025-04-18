#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>

/// @brief Single character with UI_Object functionality
class Dot : public TUI::UI_Object {
    public:
    
    Dot(TUI::Glyph glyph = {}, Vector2i pos = {0, 0}) : glyph(glyph), UI_Object(pos) {}
    TUI::Glyph glyph;

    virtual Vector2i get_size() const override { return {1, 1}; }

    protected:
    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) { tui.draw_glyph(position + origin, glyph); }
};