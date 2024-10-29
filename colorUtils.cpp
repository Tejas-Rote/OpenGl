#include "colorUtils.h"
#include <stdexcept>  // For exception handling
#include <sstream>    // For string stream conversions
#include <iomanip>    // For hex manipulation

// Helper function to convert a hex substring to an integer value
static int hexToInt(const std::string& hex) {
	int value;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> value;
	return value;
}

glm::vec3 hexToRGB(const std::string& hexColor) {
	std::string hex = hexColor;

	// Remove the '#' if it exists
	if (hex[0] == '#') {
		hex = hex.substr(1);
	}

	// Check if the length is correct for a full 6-character RGB hex
	if (hex.length() != 6) {
		throw std::invalid_argument("Invalid hex color format! Expected 6 characters.");
	}

	// Extract the individual R, G, B components from the hex string
	int r = hexToInt(hex.substr(0, 2));
	int g = hexToInt(hex.substr(2, 2));
	int b = hexToInt(hex.substr(4, 2));

	// Convert the values from 0-255 to 0-1 range and return as glm::vec3
	return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}
