#include <sztronics/tui/LineUp.hpp>
#include <algorithm>

Vector2i LineUp::get_size() const {
    int32_t line_length = 0; // aligned with lineup direction
    int32_t across_length = 0; // other coordinate

    if (perfect_spacing) {
        for (auto& child : children) {
            Vector2i child_dims = child->get_size();

            line_length += spacing + (column ? child_dims.y : child_dims.x);
            across_length = std::max(across_length, 
                                     (column ? child_dims.x : child_dims.y));
        }
        if (children.size() > 0) {
            line_length -= spacing; 
        }
    }
    else {
        for (int i{0}; i < children.size(); i++) {
            Vector2i child_dims = children[i]->get_size();

            line_length = std::max(line_length, 
                                   (column ? child_dims.y : child_dims.x) + spacing * i);
            across_length = std::max(across_length, 
                                     (column ? child_dims.x : child_dims.y));
        }
    }

    return column ? Vector2i(across_length, line_length) : 
                    Vector2i(line_length, across_length);
}

void LineUp::draw(TUI& tui, unsigned input = 0, Vector2i origin = {}) {

    if (visible)
    {
        Vector2i own_size = get_size();
        Vector2i pivot_offset = -own_size * pivot;
        // Draw self first
        draw_self(tui, input, origin + position + pivot_offset);
        Vector2i cumulative_offset = {0, 0};

        // Draw children in depth-wise succession
        for (int i{0}; i < children.size(); i++) {
            if (!children[i]) {
                continue;
            }
            UI_Object& child = *children[i];

            if (child.use_absolute_position) {
                child.draw(tui, input, origin);
            }
            else {
                Vector2i child_dimensions = child.get_size();
                // all children are drawn as if they originate from top left corner
                Vector2i pivot_adjustment = child.position - child.get_bounds().top_left;

                if (column) {
                    cumulative_offset.x = -child_dimensions.x * axis_align;
                    
                    child.draw(tui, input, origin + position + 
                                                    cumulative_offset + 
                                                    pivot_offset +
                                                    pivot_adjustment);
                    if (perfect_spacing) {
                        cumulative_offset.y += child_dimensions.y;
                    }
                    cumulative_offset.y += spacing;
                }
                else { // row
                    cumulative_offset.y = -child_dimensions.y * axis_align;

                    child.draw(tui, input, origin + position + 
                                                    cumulative_offset + 
                                                    pivot_offset +
                                                    pivot_adjustment);
                    if (perfect_spacing) {
                        cumulative_offset.x += child_dimensions.x;
                    }
                    cumulative_offset.x += spacing;
                }
            }
        }
    }
}