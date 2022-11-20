// kito-project.cpp : Defines the entry point for the application.

#include "kito_project.h"

#include <map>
#include <fmt/color.h>
#include <fmt/core.h>
#include <ft2build.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include FT_FREETYPE_H
#include "opengl/resource_manager.h"
#include "opengl/shader.h"
#include "game_loop.h"
#include "glfw/glfw_platform.h"
#include "sudoku/scenes/main_menu.h"
#include "platform.h"

/*
Entity:
geometry: Vertex, index buffers (wrt 0,0,0)
Transformations: in world space (using model matrix)
Associated shader program
*/
namespace {
constexpr float SCALE = 0.5;
constexpr int WIDTH = 1080 * SCALE;
constexpr int HEIGHT = 2400 * SCALE;
constexpr std::string_view WINDOW_NAME = "Sudoku";
}  // namespace


struct Character {
  unsigned int TextureID;  // ID handle of the glyph texture
  glm::ivec2 Size;         // Size of glyph
  glm::ivec2 Bearing;      // Offset from baseline to left/top of glyph
  unsigned int Advance;    // Offset to advance to next glyph
};
std::map<char, Character> Characters;

void drawTriangle(unsigned int vao) {
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RenderText(Shader& s, unsigned int vao, unsigned int vbo, std::string text, float x, float y,
                float scale, glm::vec3 color) {
  // activate corresponding render state
  s.Use();
  s.SetVector3f("textColor", color);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = Characters[*c];

    float xpos = x + ch.Bearing.x * scale;
    float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;
    // update VBO for each character
    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f},    {xpos, ypos, 0.0f, 1.0f},
        {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f},    {xpos + w, ypos, 1.0f, 1.0f},
        {xpos + w, ypos + h, 1.0f, 0.0f}};
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64
    // pixels)
    x += (ch.Advance >> 6) *
         scale;  // bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}




int main() {
  kito::GlfwPlatform platform = kito::GlfwPlatform{WIDTH, HEIGHT, WINDOW_NAME};
  platform.Init();
  kito::GameLoop loop(60, [&platform](double delta_time) {
    fmt::print("delta_time: {} \n", delta_time);
    platform.Update();
    return !platform.CloseRequested();
  });

  loop.Start();
  return 0;
}

int old_main(void) {
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
              << std::endl;
    return -1;
  }
  FT_Face face;
  if (FT_New_Face(ft, "res/font/ToThePoint.ttf", 0, &face)) {
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    return -1;
  }
  if ((face->face_flags & FT_FACE_FLAG_SCALABLE) != FT_FACE_FLAG_SCALABLE) {
    std::cout << "Error: font is not scalable.";
    return -1;
  }

  if (FT_Set_Pixel_Sizes(face, 0, 128)) {
    std::cout << "Error setting font pixel size";
    return -1;
  }                                       // Set font size 48px
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // disable byte-alignment restriction
  for (unsigned char c = 35; c < 128; c++) {
    // load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    fmt::print("character {}: {},{} \n", c, face->glyph->bitmap.width,
               face->glyph->bitmap.rows);
    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, 1-face->glyph->bitmap_top),
        face->glyph->advance.x};
    Characters.insert(std::pair<char, Character>(c, character));
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  unsigned int vbo, vao, ebo;
  float x1 = 10.0f;
  float y1 = 10.0f;
  float x2 = 100.0f;
  float y2 = 100.0f;
  float vertices[] = {
      x2, y1, 0.0f,  // top right
      x2, y2, 0.0f,  // bottom right
      x1, y2, 0.0f,  // bottom left
      x1, y1, 0.0f   // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  Shader shader = ResourceManager::LoadShader("res/shader/gl3/vertex.glsl",
                                              "res/shader/gl3/fragment.glsl",
                                              nullptr, "base");
  Shader text_shader = ResourceManager::LoadShader(
      "res/shader/gl3/text.vert", "res/shader/gl3/text.frag", nullptr, "text");
  glm::mat4 projection =
      glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1000.f, 1000.f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  unsigned int text_vao, text_vbo;
  glGenVertexArrays(1, &text_vao);
  glGenBuffers(1, &text_vbo);
  glBindVertexArray(text_vao);
  glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  fmt::print("Matrix {}", glm::to_string(projection));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  while (true) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    shader.SetMatrix4("projection", projection, true);
    drawTriangle(vao);
    text_shader.SetMatrix4("projection", projection, true);
    RenderText(text_shader, text_vao, text_vbo, "TANMAY", 10, 200, 0.5f,
               glm::vec3(0.5f, 0.8f, 0.2f));
  }
  return 0;
}
