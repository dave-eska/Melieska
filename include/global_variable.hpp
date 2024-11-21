#pragma once

#include <memory>

#include "player.hpp"
#include "world.hpp"

inline float PIXELS_PER_METER = 50.0f;

inline std::unique_ptr<Player> player;
inline Camera2D camera;
inline Level* level;
