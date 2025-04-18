#include <sztronics/tui/UI_Object.hpp>

TUI::UI_Object::UI_Object(int y, int x) : position(x, y) {}
TUI::UI_Object::UI_Object(Vector2i pos) : position(pos) {}

Vector2i TUI::UI_Object::get_size() const
{
    return {0, 0};
}

void TUI::UI_Object::draw(TUI& tui, unsigned input, Vector2i origin)
{
    if (visible)
    {   
        Vector2i own_size = get_size();
        Vector2i pivot_offset = -own_size * pivot;
        // Draw self first
        draw_self(tui, input, origin + position + pivot_offset);

        // Draw children in depth-wise succession
        for (auto& child_ptr : children) {
            if (!child_ptr) {
                continue;
            }
            UI_Object& child = *child_ptr;

            if (child.use_absolute_position) {
                child.draw(tui, input, origin);
            }
            else {
                Vector2i alignment_offset = own_size * child.alignment;
                child.draw(tui, input, origin + position + alignment_offset + pivot_offset);
            }
        }
    }
}