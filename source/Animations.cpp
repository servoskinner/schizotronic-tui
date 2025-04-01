#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/Animations.hpp>

Animated::Animated(float period) : timer() {
    timer.events.emplace_back([this](){ this->tick(); }, period);
}

void Animated::draw_self(TUI& tui, unsigned input, Vector2i origin)
{
    if (visible && !paused) {
        timer.process();
    }
    UI_Object::draw_self(tui, input, origin);
}

// Blinker
Blinker::Blinker(float period) : Animated(period) {}

void Blinker::tick()
{
    for (auto& child : children) {
        child->visible = !child->visible;
    }
}

// Crazy box
Crazy_box::Crazy_box(float period) : Animated(period) {}

Vector2i Crazy_box::get_size() const
{
    return rect.get_size();
}

void Crazy_box::tick()
{
    offset = (offset + 1) % ((rect.size.x + rect.size.y - 2)*2);
};

Vector2i Crazy_box::position_character(int position) 
{
    position = (position + offset) % ((rect.size.x + rect.size.y - 2)*2);

    if (position < rect.size.x + rect.size.y - 2) {
        if (position < rect.size.x - 1) {
        // top edge
            return {rect.position.x + position, rect.position.y};
        }
        else {
        // right edge
            position -= rect.size.x - 1;
            return {rect.position.x + (rect.size.x - 1), rect.position.y + position};
        }
    }
    else {
        if (position < rect.size.x*2 + rect.size.y - 3) {
        // bottom edge
            position -= rect.size.x + rect.size.y - 2;
            return {rect.position.x + (rect.size.x - 1) - position, rect.position.y + (rect.size.y - 1)};
        }
        else {
        // left edge
            position -= rect.size.x*2 + rect.size.y - 3;
            return {rect.position.x, rect.position.y + (rect.size.y - 1) - position};
        }
    }
}

void Crazy_box::draw_self(TUI& tui, unsigned input, Vector2i origin)
{
    timer.process();
    rect.draw(tui, input, origin);
    TUI::Glyph glyph = {'\0', text_color};

    int max_length = std::min((int)text.size(), (rect.size.x + rect.size.y - 2)*2);
    for (int i = 0; i < max_length; i++) {
        if (text[i] == ' ' || text[i] == '\n') {
            continue;
        }
        glyph.symbol = text[i];
        Vector2i char_pos = position_character(i);
        tui.draw_glyph(origin + char_pos, glyph);
    }
}

// Rolling text
Rolling_text::Rolling_text(float period) : Animated(period) {}

Vector2i Rolling_text::get_size() const {
    return text.get_size();
}

void Rolling_text::tick()
{
    n_drawn_chars++;
    if (n_drawn_chars > origin_text.size()) {
        n_drawn_chars = origin_text.size();
    }
    else {
        text.set_text({origin_text.begin(), origin_text.begin() + n_drawn_chars});
    }
}

void Rolling_text::draw_self(TUI& tui, unsigned input, Vector2i origin)
{   
    timer.process();
    text.draw(tui, input, origin);
}