#include "global_functions.hpp"

#include <cmath>

#include <raymath.h>

Color GetRainbowColor() {
    static float timeAccumulator = 0.0f;

    // Increment time accumulator by half of frame time
    timeAccumulator += GetFrameTime() / 4.0f;

    // Normalize the time accumulator to avoid overflow
    if (timeAccumulator > 1.0f) timeAccumulator -= 1.0f;

    // Map time to a hue value (0.0 to 1.0)
    float hue = fmod(timeAccumulator, 1.0f);

    // Convert hue to RGB values
    float r = fabs(hue * 6.0f - 3.0f) - 1.0f;
    float g = 2.0f - fabs(hue * 6.0f - 2.0f);
    float b = 2.0f - fabs(hue * 6.0f - 4.0f);

    // Clamp RGB values to [0, 1] and convert to 0-255 range
    r = Clamp(r, 0.0f, 1.0f) * 255.0f;
    g = Clamp(g, 0.0f, 1.0f) * 255.0f;
    b = Clamp(b, 0.0f, 1.0f) * 255.0f;

    return Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
}
