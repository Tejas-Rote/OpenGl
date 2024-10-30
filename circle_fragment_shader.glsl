#version 330 core
out vec4 FragColor; // Output color

in vec3 vertexColor; // Color from the vertex shader

void main() {
    FragColor = vec4(vertexColor, 1.0); // Set the fragment color to the interpolated vertex color
}
