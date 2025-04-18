#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/UI_Object.hpp>

/// @brief Lines child objects up in a row or column.
class LineUp : public TUI::UI_Object {
    public:

    enum LineUpType : bool {
        ROW = false,
        COLUMN = true
    };

    LineUp(bool is_column, Vector2i pos = {0, 0}) : UI_Object(pos), column(is_column) {}
    
    bool column = false;
    /// @brief Alignment with respect to line-up axis.
    float axis_align;

    /// @brief Absolute spacing in chars
    int32_t spacing{0};
    
    /// @brief Whether to add object's own size to each step (plus absolute spacing)
    bool perfect_spacing = true;

    virtual void draw(TUI& tui, unsigned input, Vector2i origin) override;
    virtual Vector2i get_size() const override;
};