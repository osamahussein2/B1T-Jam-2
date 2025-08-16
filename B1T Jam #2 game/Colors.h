#pragma once
#ifndef COLORS_H
#define COLORS_H

inline SDL_Color color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    SDL_Color result;
    result.r = r;
    result.g = g;
    result.b = b;
    result.a = a;
    return result;
}

const SDL_Color DARK_GREEN = {
    color(12, 73, 30, 255)
};

const SDL_Color LIGHT_GREEN = {
    color(149, 179, 132, 255)
};

#endif