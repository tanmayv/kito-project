#include <GLFW/glfw3.h>
#include <window_manager.h>
#include <glm/glm.hpp>
#include "game.h"
#include "model.h"
#include <iostream>

// void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// void processInput(GLFWwindow *window);

// settings
constexpr int SCR_WIDTH = 800;
constexpr int SCR_HEIGHT = 800;
constexpr char* TITLE = "Example Game";

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";



int main() {
  kito::Game game({.width = SCR_WIDTH, .height = SCR_HEIGHT, .title = TITLE});
  game.StartGameLoop();
  return 0;
}



/*
* Simple Render Loop
* For each entity
* Select the currect buffer
* Select the currect shader program
* Set the shader params
* make the draw call to whatever target is set
*/
