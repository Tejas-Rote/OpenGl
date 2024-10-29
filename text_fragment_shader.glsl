#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D text; // The texture sampler for the text
uniform vec3 textColor; // The color to apply to the text

void main() {
    vec4 sampled = texture(text, TexCoords);
    // Use the red channel for grayscale and multiply by text color
    FragColor = vec4(textColor, sampled.r); // Use the alpha channel for text transparency

    // Discard fragments where the texture is almost transparent
    if (sampled.r < 0.1) {
        discard; // Discard the fragment if alpha is too low
    }
}
