#version 330 core

mat4 brightnessMatrix(float b) {
    if (b > 1.0) b = 1.0;
    if (b < 0.0) b = 0.0;
    return mat4(b, 0.0f, 0.0f, 0.0f,
                0.0f, b, 0.0f, 0.0f,
                0.0f, 0.0f, b, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

in vec2 TexCoords;
out vec4 FragColor;

uniform float brightness;
uniform sampler2D texture1;

void main() {
    vec4 color = texture(texture1, TexCoords);

    FragColor = brightnessMatrix(brightness) * color;
}
