#include "Primitives\Quad.h"
#include "GL\glew.h"
#include <iostream>

void Quad::Init(unsigned int programID, Transform* transform) 
{
    _transform = transform;
    _shaderProgram = programID;
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // EBO
    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Quad::Dispose() 
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteProgram(_shaderProgram);
}

void Quad::SetTexture(const Texture& texture) 
{
    glBindVertexArray(_VAO);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.GetWidth(), texture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.GetData());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindVertexArray(0);
}

void Quad::SetUV(glm::vec2 min, glm::vec2 max) 
{
    // 0,0 
    _vertices[3] = min.x;
    _vertices[4] = min.y;

    // 0,1
    _vertices[8] = min.x;
    _vertices[9] = max.y;

    // 1,1
    _vertices[13] = max.x;
    _vertices[14] = max.y;
    
    // 1,0
    _vertices[18] = max.x;
    _vertices[19] = min.y;
}

void Quad::Draw(glm::mat4 viewProjection) 
{
    _mvp = viewProjection * _transform->GetModelMatrix();
    glUseProgram(_shaderProgram);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glBindVertexArray(_VAO);

    unsigned int mvpLoc = glGetUniformLocation(_shaderProgram, "_mvp");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &_mvp[0][0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}