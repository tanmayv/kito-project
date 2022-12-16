#include <fmt/core.h>
#include "game_loop.h"
#include "glfw/glfw_platform.h"
#include "render/renderer_interface.h"
#include "opengl/opengl_renderer.cc"
#include "sudoku/scenes/main_menu.h"
#include "platform.h"
#include "scene/scene.h"
#include "scene/scene_node.h"
#include "scene/camera_node.h"
#include "render/render_pass.h"
#include "opengl/resource_manager.h"
#include "opengl/shader.h"
#include "kito_common.h"
#include "global.h"
#include <memory>
#include <glm/ext.hpp>

namespace {
constexpr std::string_view WINDOW_NAME = "Sudoku";
}  // namespace

class TriangleNode : public kito::SceneNode {
 public:
  TriangleNode()
      : SceneNode(-1, "Root", kito::RenderPass_STATIC, glm::fvec4{},
                  &kito::IDENTITY, nullptr) {
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
   shader_ = ResourceManager::LoadShader("res/shader/gl3/vertex.glsl",
                                              "res/shader/gl3/fragment.glsl",
                                              nullptr, "standard");
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  }
  private:
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  Shader shader_;

 public:

  kito::Result PreRender(kito::Scene *scene) override {
        auto projection_ = glm::ortho(0.0f, (float)kito::global.Width(),
                             (float)kito::global.Height(), 0.0f, -1000.f, 1000.f);
    shader_.SetMatrix4("projection", projection_,
                       true);
    glBindVertexArray(vao);
    return kito::kOK;
  }

  kito::Result Render(kito::Scene *scene) override { 
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      return kito::kOK; 
  }

  kito::Result PostRender(kito::Scene *scene) override {
    glBindVertexArray(0);
    return kito::kOK;
  }

  ~TriangleNode() {

  }
   
};

class MyScene : public kito::Scene {
 public:
  MyScene(std::shared_ptr<kito::RendererInterface> renderer) {
    renderer_ = renderer;
    SetCamera(std::make_shared<kito::CameraNode>(&kito::IDENTITY));

    std::vector<glm::vec3> vertices {
        glm::vec3{199.0f,  5.5f,  0.0f},  // top right
        glm::vec3{30.5f,  50.5f,  90.0f},  // bottom right
        glm::vec3{50.5f,  90.5f,  60.0f},  // bottom left
        glm::vec3{10.5f,  70.5f,  30.0f},  // top left
    };
    std::vector<int> indexes = {
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };  
    //AddChild(1, std::make_shared<TriangleNode>(vertices, indexes));
  }
};

int main() {
  kito::global.SetWidth(500);
  kito::global.SetHeight(500);
  kito::global.SetScale(1.0f);
  kito::GlfwPlatform platform =
      kito::GlfwPlatform{kito::global.Width(), kito::global.Height(), WINDOW_NAME};
  platform.Init();
  auto renderer =
      std::shared_ptr<kito::RendererInterface>(new kito::OpenglRenderer);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  MyScene scene(renderer);
  platform.OnResize([&](int w, int h) {
    kito::global.SetWidth(w);
    kito::global.SetHeight(h);
    scene.OnRestore();
    renderer->OnRestore();
    fmt::print("Window Resized! \n");
  });
    
    //std::vector<glm::vec3> vertices {
    //    glm::vec3{199.0f,  5.5f,  0.0f},  // top right
    //    glm::vec3{30.5f,  50.5f,  0.0f},  // bottom right
    //    glm::vec3{50.5f,  90.5f,  0.0f},  // bottom left
    //    glm::vec3{10.5f,  70.5f,  0.0f},  // top left
    //};
    //std::vector<int> indexes = {
    //    // note that we start from 0!
    //    0, 1, 3,  // first triangle
    //    1, 2, 3   // second triangle
    //};  
  TriangleNode node;
  kito::GameLoop loop(60, [&](const double delta_time) {
    platform.Update();
    //scene.OnUpdate(delta_time);
    //scene.OnRender();
    renderer->ClearBackground();
    node.PreRender(&scene);
    node.Render(&scene);
    node.PostRender(&scene);
    platform.SwitchBuffer();
    return !platform.CloseRequested();
  });

  loop.Start();
  return 0;
}
