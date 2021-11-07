#version 330 core
layout (location = 0) in vec3 _pos;
uniform mat4 _mvp;

void main()
{
    gl_Position = _mvp * vec4(_pos.x, _pos.y, _pos.z, 1.0);
}