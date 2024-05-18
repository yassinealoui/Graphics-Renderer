#pragma once
#include <glm/ext/vector_float4.hpp>
#include <string>


enum class _Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    ORANGE,
    PURPLE,
    BROWN,
    PINK,
    LIME,
    TEAL,
    NAVY,
    OLIVE,
    MAROON,
    SILVER,
    GRAY,
    GOLD,
    BEIGE,
    INDIGO,
    VIOLET,
    TURQUOISE,
    MINT
};

//switch to caching
class Color
{
public:
    static glm::vec4  get(_Color color, float alpha = 1) {
        float r, g, b;
        switch (color) {
        case _Color::RED:        r = 1; g = 0; b = 0; break;
        case _Color::GREEN:      r = 0; g = 1; b = 0; break;
        case _Color::BLUE:       r = 0; g = 0; b = 1; break;
        case _Color::YELLOW:     r = 1; g = 1; b = 0; break;
        case _Color::CYAN:       r = 0; g = 1; b = 1; break;
        case _Color::MAGENTA:    r = 1; g = 0; b = 1; break;
        case _Color::ORANGE:     r = 1; g = 0.5f; b = 0; break;
        case _Color::PURPLE:     r = 0.5f; g = 0; b = 0.5f; break;
        case _Color::BROWN:      r = 0.6f; g = 0.3f; b = 0; break;
        case _Color::PINK:       r = 1; g = 0.75f; b = 0.8f; break;
        case _Color::LIME:       r = 0.75f; g = 1; b = 0; break;
        case _Color::TEAL:       r = 0; g = 0.5f; b = 0.5f; break;
        case _Color::NAVY:       r = 0; g = 0; b = 0.5f; break;
        case _Color::OLIVE:      r = 0.5f; g = 0.5f; b = 0; break;
        case _Color::MAROON:     r = 0.5f; g = 0; b = 0; break;
        case _Color::SILVER:     r = 0.75f; g = 0.75f; b = 0.75f; break;
        case _Color::GRAY:       r = 0.5f; g = 0.5f; b = 0.5f; break;
        case _Color::GOLD:       r = 1; g = 0.84f; b = 0; break;
        case _Color::BEIGE:      r = 0.96f; g = 0.96f; b = 0.86f; break;
        case _Color::INDIGO:     r = 0.29f; g = 0; b = 0.51f; break;
        case _Color::VIOLET:     r = 0.56f; g = 0; b = 1; break;
        case _Color::TURQUOISE:  r = 0.25f; g = 0.88f; b = 0.82f; break;
        case _Color::MINT:       r = 0.6f; g = 1; b = 0.6f; break;
        default:                 r = 1; g = 0; b = 0; break;
        }

        return glm::vec4(r, g, b, alpha);
    }

};