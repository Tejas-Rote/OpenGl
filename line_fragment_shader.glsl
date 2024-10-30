
#version 330 core

out vec4 FragColor;  // Output color of the fragment

in vec3 ourColor;    // Color passed from the vertex shader

void main()
{
    FragColor = vec4(ourColor, 1.0f);  // Set the output color (RGBA) using the interpolated vertex color
}
