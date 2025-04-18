#include <sztronics/tui/UI_Object.hpp>
#include <sztronics/miscellaneous/Vector2.hpp>

// Invisible UI_Object that takes up space.
class UI_Area : public TUI::UI_Object {
    public:
    UI_Area(Vector2i size = {0, 0}, Vector2i pos = {0, 0}) : UI_Object(pos), size(size) {}

    Vector2i size;
    Vector2i get_size() const override { return size; }
};