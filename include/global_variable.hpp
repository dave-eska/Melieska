#pragma once

#include <memory>

#include "player.hpp"
#include "world.hpp"

inline std::unique_ptr<Player> player;
inline Camera2D camera;
inline std::unique_ptr<Level> level;
