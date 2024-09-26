#include <__config>
#include <iostream>
#include <test.hpp>
#include <util/configuration.hpp>

#include <GLFW/glfw3.h>
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

int main(int, char **) {
  glfwInit();
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "hellp bgfx", nullptr, nullptr);

  bgfx::PlatformData pd;
  pd.nwh = glfwGetCocoaWindow(window);
  bgfx::setPlatformData(pd);

  bgfx::Init bgfxInit;
  bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
  bgfxInit.resolution.width = 800;
  bgfxInit.resolution.height = 600;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfx::init(bgfxInit);

  return 0;
}
