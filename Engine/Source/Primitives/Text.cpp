#include "Primitives\Text.h"
#include "Resources\ShaderLoader.h"
#include "Log.h"
#include "GL\glew.h"
#include <glm/gtc/matrix_transform.hpp>

void Text::Init(const char* font, int fontSize) 
{
	ShaderLoader shaderLoader;
	_shaderProgram = shaderLoader.LoadTextShader();
	if (FT_Init_FreeType(&_fontLibrary)) 
	{
		Log::LogError("Error while initializing the FreeType Library.");
		return;
	}

	FT_Face face;
	if (FT_New_Face(_fontLibrary,font,0, &face)) 
	{
		Log::LogError("Error while loading font: %s.", "Error", font);
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction.

	for (unsigned char c = 0; c < 128; c++) 
	{
		// Load charachter
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			Log::LogError("Failed to load Glyph for charachter: %s", "Error", c);
		}

		// Generate texture
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_RED, 
			face->glyph->bitmap.width, 
			face->glyph->bitmap.rows, 
			0, 
			GL_RED, 
			GL_UNSIGNED_BYTE, 
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		Charachter charachter = {
			textureID,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		_storedCharacters.insert(std::pair<char, Charachter>(c, charachter));
	}
	
	// Initialize shaders
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	FT_Done_Face(face);
	FT_Done_FreeType(_fontLibrary);
}

void Text::Dispose() 
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteProgram(_shaderProgram);
}

void Text::SetProjection(glm::mat4 projection) 
{
	glUseProgram(_shaderProgram);
	unsigned int location = glGetUniformLocation(_shaderProgram, "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, &projection[0][0]);
}

void Text::Draw(const char* text, glm::vec2 pos, float scale, glm::vec3 color) 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(_shaderProgram);

	glUniform3f(glGetUniformLocation(_shaderProgram, "textColor"), 1.f, 1.f, 1.f);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_VAO);

	const char* ptr = text;
	for (char c = *ptr; c; c = *++ptr) {
		Charachter ch = _storedCharacters[*ptr];

		float xpos = pos.x + ch.bearing.x * scale;
		float ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		pos.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
