#version 330 core
layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 color;    // Vertex color

out vec3 vertexColor; // Output color to the fragment shader

uniform mat4 model;       // Model matrix
uniform mat4 view;        // View matrix
uniform mat4 projection;   // Projection matrix

void main() {
    // Transform the vertex position
    gl_Position = projection * view * model * vec4(position, 1.0);
    vertexColor = color; // Pass the vertex color to the fragment shader
}
