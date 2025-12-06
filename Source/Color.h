#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <algorithm>

// use alias to clarify type name
using color3_t = glm::vec3;
using color4_t = glm::vec4;

// convert from RGBA(0.0 - 1.0) color to (0 - 255) color
inline SDL_Color ColorConvert(const color4_t& color4)
{
	SDL_Color color;
	color.r = static_cast<Uint8>(glm::clamp(color4.r, 0.0f, 1.0f) * 255.0f);
	color.g = static_cast<Uint8>(glm::clamp(color4.g, 0.0f, 1.0f) * 255.0f);
	color.b = static_cast<Uint8>(glm::clamp(color4.b, 0.0f, 1.0f) * 255.0f);
	color.a = static_cast<Uint8>(glm::clamp(color4.a, 0.0f, 1.0f) * 255.0f);
	return color;
}

// convert from RGB(0.0 - 1.0) color to (0 - 255) color
inline SDL_Color ColorConvert(const color3_t& color3)
{
	SDL_Color color;
	color.r = static_cast<Uint8>(glm::clamp(color3.r, 0.0f, 1.0f) * 255.0f);
	color.g = static_cast<Uint8>(glm::clamp(color3.g, 0.0f, 1.0f) * 255.0f);
	color.b = static_cast<Uint8>(glm::clamp(color3.b, 0.0f, 1.0f) * 255.0f);
	color.a = 255;
	return color;
}

// convert from (0 - 255) color to RGBA(0.0 - 1.0) color
inline color4_t ColorConvert(const SDL_Color& color)
{
	color4_t color4;
	color4.r = static_cast<float>(color.r) / 255.0f;
	color4.g = static_cast<float>(color.g) / 255.0f;
	color4.b = static_cast<float>(color.b) / 255.0f;
	color4.a = static_cast<float>(color.a) / 255.0f;
	return color4;
}
