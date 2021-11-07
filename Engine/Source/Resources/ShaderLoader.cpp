#include "Resources\ShaderLoader.h"
#include <string>
#include <iostream>
#include <fstream>

int ShaderLoader::LoadDefaultShaders() 
{
    ShaderData vertex = LoadShader("Assets/Shaders/basic.vert", ShaderType::Vertex);
    ShaderData fragment = LoadShader("Assets/Shaders/basic.frag", ShaderType::Fragment);
    return LinkShaders(vertex, fragment);
}

int ShaderLoader::LoadLineShader() 
{
    ShaderData vertex = LoadShader("Assets/Shaders/line.vert", ShaderType::Vertex);
    ShaderData fragment = LoadShader("Assets/Shaders/line.frag", ShaderType::Fragment);
    return LinkShaders(vertex, fragment);
}

int ShaderLoader::LoadTextShader()
{
    ShaderData vertex = LoadShader("Assets/Shaders/text.vert", ShaderType::Vertex);
    ShaderData fragment = LoadShader("Assets/Shaders/text.frag", ShaderType::Fragment);
    return LinkShaders(vertex, fragment);
}

int ShaderLoader::LinkShaders(const ShaderData& vertex, const ShaderData& fragment) 
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex.shaderID);
    glAttachShader(shaderProgram, fragment.shaderID);
    glLinkProgram(shaderProgram);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader linking failed.\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex.shaderID);
    glDeleteShader(fragment.shaderID);
    return shaderProgram;
}

ShaderData ShaderLoader::LoadShader(const char* file, ShaderType type) 
{
    ShaderData shader;
    std::string data;
    if (!LoadFile(file, &data)) 
    {
        std::cout << "Error while loading shader: " << file << std::endl;
        return shader;
    }

    switch (type)
    {
    case ShaderType::Vertex:
        shader.shaderID = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::Fragment:
        shader.shaderID = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        std::cout << "Unsupported shader type." << std::endl;
        return shader;
    }

    const char* src = data.c_str();
    glShaderSource(shader.shaderID, 1, &src, NULL);
    glCompileShader(shader.shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shader.shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader.shaderID, 512, NULL, infoLog);
        std::cout << "Error while compiling shader: " << file << "Log: \n" << infoLog << std::endl;
    }

    return shader;
}

int ShaderLoader::LoadFile(const char* filename, std::string* out) 
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        getline(file, *out, (char)file.eof());
        file.close();
        return 1;
    }

    return -1;
}