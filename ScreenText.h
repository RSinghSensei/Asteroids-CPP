#pragma once
#include <glm-0.9.9.8/glm/glm.hpp>
#include <map>
#include "Shader.h"
#include <glad/glad.h>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>


struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

std::map<char, Character> Characters;

void initandaddtoMap()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) { std::cout << "Failed to initiaiize Freetype" << std::endl; return; }
    FT_Face face;
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) { std::cout << "Failed to initialize font" << std::endl; return; }

    FT_Set_Pixel_Sizes(face, 0, 48);
    for (unsigned char i = 0; i < 128; i++)
    {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
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
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character tempcharacter = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x

        };
        Characters[i] = tempcharacter;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

}

class RenderText
{
    RenderText();
    ~RenderText();

    void renderFunction(Shader &s2, GLuint st_T, const std::string& text, float x, float y, float scale, const glm::vec3& color);
private:
    GLuint VAO;
    GLuint VBO;


};


RenderText::RenderText()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

RenderText::~RenderText(){}

void RenderText::renderFunction(Shader& s2, GLuint st_T, const std::string& text, float x, float y, float scale, const glm::vec3& color)
{
    glUseProgram(st_T);
    glUniform3f(glGetUniformLocation(st_T, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
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
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
