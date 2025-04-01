#pragma once

#include <sztronics/tui/TUI.hpp>
#include <sztronics/tui/Sprite.hpp>
#include <sztronics/miscellaneous/Archivist.hpp>
#include <sztronics/miscellaneous/Serialization.hpp>
#include <sztronics/miscellaneous/Misc_functions.hpp>

#include <vector>
#include <string>
#include <optional>

/// @brief Writes sprite data into a file.
bool save_sprite(Sprite& sprite, std::string filename);
/// @brief Creates sprite from a file.
std::optional<Sprite> load_sprite(std::string filename);