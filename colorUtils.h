#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <glm/glm.hpp>
#include <string>

// Converts a hex color code (e.g., "#FF5733") to glm::vec3 (RGB values normalized to [0, 1])
glm::vec3 hexToRGB(const std::string& hexColor);

#endif // COLOR_UTILS_H
