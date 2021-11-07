#pragma once
#include "API.h"
#include <map>
#include <glm\glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H 

struct Charachter {
	unsigned int textureID = 0;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Text 
{
private:
	unsigned int _VBO, _VAO;
	unsigned int _shaderProgram;
	FT_Library _fontLibrary;
	std::map<char, Charachter> _storedCharacters;
public:
	ENGINE_API void Init(const char* font = "Assets/Fonts/FallingSkyBlack.otf",int fontSize = 48);
	ENGINE_API void Dispose();
	ENGINE_API void SetProjection(glm::mat4 projection);
	ENGINE_API void Draw(const char*, glm::vec2 position, float scale, glm::vec3 color);
};
