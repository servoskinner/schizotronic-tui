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
        // Draw self first
        draw_self(tui, input, origin + position);

        // Draw children in depth-wise succession
        for (auto& child : children) {
            if (child->use_absolute_position) {
                child->draw(tui, input, origin);
            }
            else {
                Vector2i child_dimensions = child->get_size();
                Vector2i offset = get_size() - child_dimensions;

                Vector2i anchor_offset = { (offset.x * (int)child->horizontal_anchor)/2, (offset.y * (int)child->vertical_anchor)/2 };

                child->draw(tui, input, origin + position + anchor_offset);
            }
        }
    }
}