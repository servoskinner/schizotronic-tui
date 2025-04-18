#include <sztronics/tui/Text.hpp>

Text::Text(std::string text, Vector2i constraints, Vector2i position, 
           TUI::Color foreground, TUI::Color background) : \
           raw_text(text), constraints(constraints), background(background), foreground(foreground), UI_Object(position)
{
   set_text(text);
}

void Text::draw_self(TUI& tui, unsigned input, Vector2i origin)
{
    int vertical_offset = 0;
    for (const std::string line : text_lines) {
        tui.print(line, origin + Vector2i(0, vertical_offset), foreground, background);
        vertical_offset++;
    }
}

Vector2i Text::get_size() const {
    if (fill_max_size) {
        return constraints;
    }
    else {
        int y_size = text_lines.size();
        int x_size = 0;

        for (const std::string& line : text_lines) {
            x_size = std::max(x_size, (int)line.size());
        }
        return {x_size, y_size};
    }
}

void Text::set_xylimit(Vector2i xy_lim) {
    if (constraints != xy_lim) {
        constraints = xy_lim;
        refit_text();
    }
}

void Text::set_xlimit(int x_lim) {
    if (x_lim != constraints.x) {
        constraints.x = x_lim;
        refit_text();
    }
}

void Text::set_ylimit(int y_lim) {
    if (y_lim != constraints.y) {
        constraints.y = y_lim;
        refit_text();
    }
}

void Text::set_text(std::string new_text) {
    raw_text = new_text;
    refit_text();
}

void Text::set_wrap(bool value) {
    if (wrap != value) {
        wrap = value;
        refit_text();
    }
}

void Text::refit_text() {
    if (wrap) {
        text_lines = wrap_text(raw_text, constraints.x);
        if (constraints.y > 0 && text_lines.size() > constraints.y) {
            text_lines.resize(constraints.y);
        }
    }
    else {
        // No wrap -- trim individual lines instead
        text_lines = {};
        std::string line = "";
        for(char ch : raw_text) {
            if (ch != '\n') {
                if(constraints.x <= 0 || line.size() < constraints.x) {
                    line += ch;
                }
            }
            else if (constraints.y <= 0 || text_lines.size() < constraints.y) {
                text_lines.emplace_back(std::move(line));
            }
            else {
                break;
            }
        }
    }
}