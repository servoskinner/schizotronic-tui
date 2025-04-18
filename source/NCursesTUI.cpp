#include <sztronics/tui/NCursesTUI.hpp>
#include <sztronics/miscellaneous/Misc_functions.hpp>

#include <iostream>

// Static vars
std::mutex NCursesTUI::ncurses_mutex {};
std::optional<std::lock_guard<std::mutex>> NCursesTUI::ncurses_mtx_lock {};

bool NCursesTUI::mouse_enabled = false;

TUI& NCursesTUI::get(bool with_mouse)
{  
    static NCursesTUI instance;
    if (with_mouse) {
        enable_mouse();
    }
    return instance;
}

Vector2i NCursesTUI::get_screen_size() const { 
    return {getmaxx(stdscr), getmaxy(stdscr)};
}

NCursesTUI::NCursesTUI() 
{
    ncurses_mtx_lock.emplace(ncurses_mutex);

    initscr();

    cbreak();                  // No line buffering for keys
    noecho();               // Do not echo characters in terminal
    curs_set(0);            // Hide cursor   
    timeout(0);             // Do not block when getting input

    start_color(); 
    // init color pairs
    for(unsigned char fore = 0; fore < 16; fore++) {
        for(unsigned char back = 0; back < 16; back++) {
            set_color_pair(get_color_code((Color)fore, (Color)back), fore, back);
        }
    }
    ncurses_mtx_lock.reset();
}

NCursesTUI::~NCursesTUI() 
{
    endwin();
}

unsigned short NCursesTUI::get_color_code(Color foreground, Color background) const
{
    // Remove transparent parts
    if (background == TRANSPARENT) {
        background = default_background == TRANSPARENT ? BLACK : default_background;
    }
    if (foreground == TRANSPARENT) {
        foreground = background;
    }
    // (WHITE, BLACK) and (BLACK, BLACK) are swapped
    if (background == BLACK) {
        if (foreground == WHITE) {
            return 0U;
        }
        if (foreground == BLACK) {
            return (unsigned short)BLACK * 16 + (unsigned short)WHITE;
        }
    }
    // All other colors are mapped normally
    return (unsigned short)background * 16 + (unsigned short)foreground;
}

void NCursesTUI::output_glyph(Vector2i pos, Glyph glyph) {
    attron(COLOR_PAIR(get_color_code(glyph.foreground, glyph.background)));
    mvaddch(pos.y, pos.x, glyph.symbol);
    attroff(COLOR_PAIR(get_color_code(glyph.foreground, glyph.background)));
}

void NCursesTUI::enable_mouse() {
    ncurses_mtx_lock.emplace(ncurses_mutex);

    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED | BUTTON1_PRESSED |
              BUTTON3_CLICKED | BUTTON3_PRESSED,
              nullptr);
    mouse_enabled = true;
}

void NCursesTUI::disable_mouse() {
    ncurses_mtx_lock.emplace(ncurses_mutex);

    keypad(stdscr, FALSE);
    mousemask(0, nullptr); 
    mouse_enabled = false;
}

void NCursesTUI::pre_render() { 
    ncurses_mtx_lock.emplace(ncurses_mutex); 
    // Read input
    unsigned input = getch();

    if (mouse_enabled && input == KEY_MOUSE) { // Mouse
        MEVENT mouse_event;
        if (getmouse(&mouse_event) == OK) {
            last_mouse.pos = {mouse_event.x, mouse_event.y};
            last_mouse.left = (mouse_event.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED));
            last_mouse.right = (mouse_event.bstate & (BUTTON3_PRESSED | BUTTON3_CLICKED));
        }
        last_input = 0;
    }
    else {
        last_mouse.left = false; last_mouse.right = false;
        
        if (input == (unsigned)ERR) { // Error
            last_input = 0;
        }
        else { // Normal input
            last_input = input;
        }
    }
}

void NCursesTUI::post_render() { 
    ncurses_mtx_lock.reset(); 
}

unsigned NCursesTUI::get_input(){
    return last_input;
}

TUI::MouseState NCursesTUI::get_mouse() {
    return mouse_enabled ? last_mouse : MouseState{};
}

void NCursesTUI::make_pretty(Rect& rect) {
    rect.tl_corner.symbol = ACS_ULCORNER;
    rect.tr_corner.symbol = ACS_URCORNER;
    rect.bl_corner.symbol = ACS_LLCORNER;
    rect.br_corner.symbol = ACS_LRCORNER;

    rect.t_border.symbol = ACS_HLINE;
    rect.r_border.symbol = ACS_VLINE;
    rect.b_border.symbol = ACS_HLINE;
    rect.l_border.symbol = ACS_VLINE;
}
