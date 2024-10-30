#version 330 core
in vec3 fragColor; // Receive the color from the vertex shader
out vec4 color;

void main() {
    color = vec4(fragColor, 1.0); // Use the color passed from the vertex shader
}
