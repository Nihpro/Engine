#version 330 core
in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
    vec4 texColor = texture(texture1, TexCoord);
    FragColor = texColor * vec4(Color, 1.0);
}