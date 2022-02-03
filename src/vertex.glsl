#version 330 core
layout (location = 0) in vec3 aPos;
uniform float offset;
out vec4 pos_color;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    pos_color = vec4(aPos, 1.0);
};