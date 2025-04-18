#pragma once

#include <sztronics/tui/TUI.hpp>

/// @brief Generic TUI Object, multiple can be composed in hierarchical order.
class TUI::UI_Object
{
    public:
    UI_Object(int y = 0, int x = 0);
    UI_Object(Vector2i pos);
    UI_Object& operator= (const UI_Object& other) = default;

    Vector2i position; 
    /// @brief If set to true, ignore positioning relative to parent

    bool use_absolute_position = false;
    bool visible = true;
    std::vector<std::shared_ptr<UI_Object>> children = {};

    Vector2f pivot{0, 0};
    Vector2f alignment{0, 0};

    static constexpr float ALIGN_START = 0.0;
    static constexpr float ALIGN_MIDDLE = 0.5;
    static constexpr float ALIGN_END = 1.0;

    virtual void draw(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0});
    virtual Vector2i get_size() const;

    struct Bounds {
        Vector2i top_left;
        Vector2i bottom_right;
    };
    /// @brief Returns the object's axis-aligned bounding box
    inline Bounds get_bounds() const {
        Vector2i own_size = get_size();
        Vector2i top_left = position - own_size * pivot;
        return {top_left, top_left + own_size};
    }

    virtual bool is_within(Vector2i pos) {
        return is_within(pos, get_bounds());
    }

    static inline bool is_within(Vector2i pos, Bounds bounds) {
        return (pos >= bounds.top_left) && (pos < bounds.bottom_right);
    }

    protected:
    virtual void draw_self(TUI& tui, unsigned input = 0, Vector2i origin = {0, 0}) {}
};