#include "Primitives\Line.h"
#include "GL\glew.h"

void Line::Init(unsigned int programID)
{
    _shaderProgram = programID;

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Line::Clear()
{
    unsigned int lastSize = _vertices.size();
    _vertices.clear();

    // There is a good posibility we will update and have the same amount of vertices next frame.
    // Todo: Move this to a new fucntion as clear should remove all data in the line class.
    _vertices.reserve(lastSize);
    UpdateBuffers();
}

void Line::Draw(glm::mat4 viewProjection)
{
    assert(_vertices.size() != 0 && "Vertices not initialized.");
    // Remove the camera's distance from view projection to ensure correct line positions.
    _mvp = viewProjection;

    glUseProgram(_shaderProgram);

    GLint mvpLocation = glGetUniformLocation(_shaderProgram, "_mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &_mvp[0][0]);

    GLint colorLocation = glGetUniformLocation(_shaderProgram, "_color");
    glUniform4f(colorLocation, _color.r, _color.g, _color.b, _color.a);

    glBindVertexArray(_VAO);
    glDrawArrays(GL_LINES, 0, _vertices.size());
}

void Line::AddLine(glm::vec3 start, glm::vec3 end)
{
    _vertices.push_back(start);
    _vertices.push_back(end);
}

void Line::UpdateBuffers()
{
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
}