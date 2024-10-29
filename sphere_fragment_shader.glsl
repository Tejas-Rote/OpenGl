#version 330 core

in vec3 fragColor; // Input from vertex shader

out vec4 outputColor; // Final output color

void main() {
    outputColor = vec4(fragColor, 1.0); // Set the output color (RGBA)
}
