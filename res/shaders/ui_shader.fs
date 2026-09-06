#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec4 color;

void main() {
    vec4 texColor = texture(texture1, TexCoord);

    if(texColor.a < 0.01) {
	discard;
    }

    FragColor = texColor * color;
}