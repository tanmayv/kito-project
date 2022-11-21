#include "render/renderer_interface.h"
#include "global.h"
#include <glad/glad.h>


namespace kito {
class OpenglRenderer : public RendererInterface {
 public:
  OpenglRenderer() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    }  	

    glViewport(0, 0, global.Width(), global.Height());
  }

  void OnRestore() override {
    glViewport(0, 0, global.Width(), global.Height());
  }

  void ClearBackground() override {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
};

}
