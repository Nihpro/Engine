#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projectionMat;
uniform mat4 modelMat;

void main() {
    gl_Position = projectionMat * modelMat * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
yy