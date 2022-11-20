#include "text_renderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace kito {
bool TextRenderer::Init(std::string_view font_file, int font_size) {
  // FT_Library ft;
  // if (FT_Init_FreeType(&ft)) {
  //   std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
  //             << std::endl;
  //   return -1;
  // }
  // FT_Face face;
  // if (FT_New_Face(ft, "res/font/ToThePoint.ttf", 0, &face)) {
  //   std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
  //   return -1;
  // }
  // if ((face->face_flags & FT_FACE_FLAG_SCALABLE) != FT_FACE_FLAG_SCALABLE) {
  //   std::cout << "Error: font is not scalable.";
  //   return -1;
  // }

  // if (FT_Set_Pixel_Sizes(face, 0, 128)) {
  //   std::cout << "Error setting font pixel size";
  //   return -1;
  // }  // Set font size 48px
  // glPixelStorei(GL_UNPACK_ALIGNMENT,
  //               1);  // disable byte-alignment restriction
  // for (unsigned char c = 35; c < 128; c++) {
  //   // load character glyph
  //   if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
  //     std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
  //     continue;
  //   }
  //   fmt::print("character {}: {},{} \n", c, face->glyph->bitmap.width,
  //              face->glyph->bitmap.rows);
  //   // generate texture
  //   unsigned int texture;
  //   glGenTextures(1, &texture);
  //   glBindTexture(GL_TEXTURE_2D, texture);
  //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
  //                face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
  //                face->glyph->bitmap.buffer);
  //   // set texture options
  //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //   // now store character for later use
  //   Character character = {
  //       texture,
  //       glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
  //       glm::ivec2(face->glyph->bitmap_left, 1 - face->glyph->bitmap_top),
  //       face->glyph->advance.x};
  //   Characters.insert(std::pair<char, Character>(c, character));
  // }
  // FT_Done_Face(face);
  // FT_Done_FreeType(ft);
  return true;
}

void TextRenderer::RenderText(int x, int y, std::string_view message,
                              double scale) {}
}  // namespace kito
