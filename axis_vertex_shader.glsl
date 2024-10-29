#version 330 core

layout(location = 0) in vec3 position; // Input position
layout(location = 1) in vec3 color;    // Input color

out vec3 fragColor; // Output color to the fragment shader

uniform mat4 transform; // Transformation matrix

void main() {
    gl_Position = transform * vec4(position, 1.0); // Apply transformation
    fragColor = color; // Pass color to fragment shader
}
