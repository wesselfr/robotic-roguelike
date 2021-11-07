#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec2 _uv;

uniform mat4 _mvp;

out vec2 uvCoords;

void main()
{
    gl_Position = _mvp * vec4(_pos.x, _pos.y, _pos.z, 1.0);
    uvCoords = _uv;
}