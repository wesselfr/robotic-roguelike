#version 330 core
out vec4 FragColor;

in vec2 uvCoords;
uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, uvCoords).r);
    FragColor = vec4(textColor, 1.0) * sampled;
} 
