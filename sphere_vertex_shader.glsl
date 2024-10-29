#version 330 core

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 color;    // Vertex color

uniform mat4 transform; // Transformation matrix

out vec3 fragColor; // Output to the fragment shader

void main() {
    gl_Position = transform * vec4(position, 1.0); // Apply transformation
    fragColor = color; // Pass color to fragment shader
}
