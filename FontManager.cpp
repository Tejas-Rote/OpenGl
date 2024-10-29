//// FontManager.cpp
//#include "FontManager.h"
//#include <iostream>
//#include <glad/glad.h>
//
//FontManager::FontManager() {
//	// Initialize FreeType
//	if (FT_Init_FreeType(&ft)) {
//		std::cerr << "Could not initialize FreeType Library" << std::endl;
//	}
//
//	// Set up OpenGL buffers for text rendering
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//	glEnableVertexAttribArray(0);
//}
//
//FontManager::~FontManager() {
//	FT_Done_FreeType(ft);
//}
//
//void FontManager::loadFont(const std::string& path, unsigned int fontSize) {
//	FT_Face face;
//	if (FT_New_Face(ft, path.c_str(), 0, &face)) {
//		std::cerr << "Failed to load font: " << path << std::endl;
//		return;
//	}
//
//	FT_Set_Pixel_Sizes(face, 0, fontSize);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	for (unsigned char c = 0; c < 128; c++) {
//		// Load glyph
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//			std::cerr << "Failed to load Glyph" << std::endl;
//			continue;
//		}
//
//		// Generate texture
//		GLuint texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		// Store character data
//		characters.insert(std::pair<char, Character>(c, Character{ texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			static_cast<GLuint>(face->glyph->advance.x) }));
//	}
//
//	FT_Done_Face(face);
//}
//
//void FontManager::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
//	// Activate the appropriate shader
//	// Assuming you have a shader program set up
//	glUseProgram(/* Your Shader Program ID */);
//	glUniform3f(glGetUniformLocation(/* Your Shader Program ID */, "textColor"), color.x, color.y, color.z);
//	glActiveTexture(GL_TEXTURE0);
//	glBindVertexArray(VAO);
//
//	for (const char& c : text) {
//		Character ch = characters[c];
//
//		float xpos = x + ch.bearing.x * scale;
//		float ypos = y - (ch.size.y - ch.bearing.y) * scale; // In OpenGL, y-coordinates go upwards
//
//		float w = ch.size.x * scale;
//		float h = ch.size.y * scale;
//
//		// Update VBO for each character
//		float vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
//			{ xpos,     ypos,       0.0f, 1.0f }, // Bottom-left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom-right
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom-right
//			{ xpos + w, ypos + h,   1.0f, 0.0f }  // Top-right
//		};
//
//		// Render the glyph texture over the quad
//		glBindTexture(GL_TEXTURE_2D, ch.textureID);
//
//		// Update VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Update buffer contents
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//		// Draw the quad
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// Advance the cursor for the next glyph
//		x += (ch.advance >> 6) * scale; // Bit-shift to convert from 1/64th to 1.0
//	}
//
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}

//#include "FontManager.h"
//#include <iostream>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include <glad/glad.h> // Make sure to include GLAD for OpenGL
//
//// Constructor to initialize FreeType and create the font VAO/VBO
//FontManager::FontManager() {
//	// Initialize FreeType
//	if (FT_Init_FreeType(&ft)) {
//		std::cerr << "Could not initialize FreeType Library" << std::endl;
//	}
//
//	// Generate VAO and VBO for rendering text
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	// Bind the VAO
//	glBindVertexArray(VAO);
//
//	// Create a VBO to hold the text quad vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW); // Reserve space for 6 vertices (2 triangles)
//
//	// Set vertex attributes
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// Unbind VAO
//	glBindVertexArray(0);
//}
//
//// Destructor to clean up resources
//FontManager::~FontManager() {
//	// Cleanup FreeType library
//	FT_Done_FreeType(ft);
//
//	// Delete VAO and VBO
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// Delete character textures
//	for (auto& pair : characters) {
//		glDeleteTextures(1, &pair.second.textureID);
//	}
//}
//
//// Load a font and generate character textures
//void FontManager::loadFont(const std::string& path, unsigned int fontSize) {
//	// Load the font face
//	FT_Face face;
//	if (FT_New_Face(ft, path.c_str(), 0, &face)) {
//		std::cerr << "Failed to load font: " << path << std::endl;
//		return;
//	}
//
//	// Set the font size
//	FT_Set_Pixel_Sizes(face, 0, fontSize);
//
//	// Load characters (glyphs)
//	for (unsigned char c = 0; c < 128; c++) {
//		// Load glyph for the character
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//			std::cerr << "Failed to load glyph for character: " << c << std::endl;
//			continue;
//		}
//
//		// Generate a texture for each character
//		GLuint texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
//			face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
//			face->glyph->bitmap.buffer);
//
//		// Set texture parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		// Store the character data in a map
//		Character character = {
//			texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			static_cast<unsigned int>(face->glyph->advance.x)
//		};
//		characters.insert(std::pair<char, Character>(c, character));
//	}
//
//	// Clean up FreeType face
//	FT_Done_Face(face);
//}
//
//// Render the text on the screen
//void FontManager::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color, Shader& shader) {
//	// Activate the shader and set color
//	shader.use(); // Pass the shader object as an argument
//	shader.setVec3("textColor", color); // Set the color uniform for text rendering
//
//	// Bind the VAO for text rendering
//	glBindVertexArray(VAO);
//
//	// Iterate through all characters in the string
//	for (char c : text) {
//		Character ch = characters[c];
//
//		// Calculate the position for each character
//		float xpos = x + ch.bearing.x * scale; // Bearing x
//		float ypos = y - (ch.size.y - ch.bearing.y) * scale; // Bearing y
//
//		// Calculate the dimensions of the quad
//		float w = ch.size.x * scale;
//		float h = ch.size.y * scale;
//
//		// Update VBO for each character
//		GLfloat vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
//			{ xpos,     ypos,       0.0f, 1.0f }, // Bottom left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
//			{ xpos + w, ypos + h,   1.0f, 0.0f }  // Top right
//		};
//
//		// Render the glyph texture over the quad
//		glBindTexture(GL_TEXTURE_2D, ch.textureID);
//
//		// Update VBO and render the quad
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// Advance the cursor for the next glyph
//		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th of a pixel)
//	}
//
//	// Unbind the VAO
//	glBindVertexArray(0);
//}


#include "FontManager.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

// Constructor to initialize FreeType and create the font VAO/VBO
FontManager::FontManager() {
	// Initialize FreeType
	if (FT_Init_FreeType(&ft)) {
		std::cerr << "ERROR: Could not initialize FreeType Library" << std::endl;
	}
	else {
		std::cout << "INFO: FreeType initialized successfully" << std::endl;
	}

	// Generate VAO and VBO for rendering text
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the VAO
	glBindVertexArray(VAO);

	// Create a VBO to hold the text quad vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW); // Reserve space for 6 vertices (2 triangles)

	// Set vertex attributes
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);
}

// Destructor to clean up resources
FontManager::~FontManager() {
	// Cleanup FreeType library
	FT_Done_FreeType(ft);
	std::cout << "INFO: FreeType library cleaned up" << std::endl;

	// Delete VAO and VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	std::cout << "INFO: VAO and VBO deleted" << std::endl;
}

// Load a font and generate character textures
void FontManager::loadFont(const std::string& path, unsigned int fontSize) {
	// Load the font face
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face)) {
		std::cerr << "Failed to load font: " << path << std::endl;
		return;
	}

	// Set the font size
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	std::cout << "INFO: Font size set to: " << fontSize << std::endl;

	// Load characters (glyphs)
	for (unsigned char c = 32; c < 128; c++) { // Load printable characters
		// Load glyph for the character
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "Failed to load glyph for character: " << c << std::endl;
			continue;
		}

		// Generate a texture for each character
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
			face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Store the character data in a map
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		characters.insert(std::pair<char, Character>(c, character));
		std::cout << "INFO: Loaded character: " << c << " (Texture ID: " << texture << ")" << std::endl;
	}

	// Clean up FreeType face
	FT_Done_Face(face);
	std::cout << "INFO: FreeType face cleaned up" << std::endl;
}

// Render the text on the screen
//void FontManager::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color, Shader& shader) {
//	// Activate the shader and set color
//	shader.use(); // Pass the shader object as an argument
//	shader.setVec3("textColor", color); // Set the color uniform for text rendering
//
//	// Bind the VAO for text rendering
//	glBindVertexArray(VAO);
//
//	// Iterate through all characters in the string
//	for (char c : text) {
//		if (characters.find(c) == characters.end()) {
//			std::cerr << "ERROR: Character not found in characters map: " << c << std::endl;
//			continue; // Skip rendering if character not found
//		}
//
//		Character ch = characters[c];
//
//		// Calculate the position for each character
//		float xpos = x + ch.bearing.x * scale; // Bearing x
//		float ypos = y - (ch.size.y - ch.bearing.y) * scale; // Bearing y
//
//		// Calculate the dimensions of the quad
//		float w = ch.size.x * scale;
//		float h = ch.size.y * scale;
//
//		// Update VBO for each character
//		GLfloat vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
//			{ xpos,     ypos,       0.0f, 1.0f }, // Bottom left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
//			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
//			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
//			{ xpos + w, ypos + h,   1.0f, 0.0f }  // Top right
//		};
//
//		// Render the glyph texture over the quad
//		glBindTexture(GL_TEXTURE_2D, ch.textureID);
//
//		// Update VBO and render the quad
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// Advance the cursor for the next glyph
//		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th of a pixel)
//	}
//
//	// Unbind the VAO
//	glBindVertexArray(0);
//}


void FontManager::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color, Shader& shader) {
	// Activate the shader and set color
	shader.use(); // Pass the shader object as an argument
	shader.setVec3("textColor", color); // Set the color uniform for text rendering

	// Bind the VAO for text rendering
	glBindVertexArray(VAO);

	// Iterate through all characters in the string
	for (char c : text) {
		if (characters.find(c) == characters.end()) {
			std::cerr << "ERROR: Character not found in characters map: " << c << std::endl;
			continue; // Skip characters that are not found
		}

		Character ch = characters[c];

		// Calculate the position for each character
		float xpos = x + ch.bearing.x * scale; // Bearing x
		float ypos = y - (ch.size.y - ch.bearing.y) * scale; // Inverted y-axis calculation

		// Calculate the dimensions of the quad
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
			{ xpos,     ypos,       0.0f, 1.0f }, // Bottom left
			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
			{ xpos,     ypos + h,   0.0f, 0.0f }, // Top left
			{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
			{ xpos + w, ypos + h,   1.0f, 0.0f }  // Top right
		};

		// Render the glyph texture over the quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// Update VBO and render the quad
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Advance the cursor for the next glyph
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th of a pixel)
	}

	// Unbind the VAO
	glBindVertexArray(0);
}
