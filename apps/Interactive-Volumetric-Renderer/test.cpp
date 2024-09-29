// #include <iostream>
// #include <test.hpp>
// #include <util/configuration.hpp>
//
// #include <GLFW/glfw3.h>
// #ifdef _WIN32
// #define GLFW_EXPOSE_NATIVE_WIN32
// #else
// #define GLFW_EXPOSE_NATIVE_COCOA
// #endif
// #include <GLFW/glfw3native.h>
//
// #include <bgfx/bgfx.h>
// #include <bgfx/platform.h>
//
// #include <test.hpp>

// int main(int, char **) {
//   glfwInit();
//   GLFWwindow *window =
//       glfwCreateWindow(800, 600, "hellp bgfx", nullptr, nullptr);
//
//   // Too old to use!
//   // bgfx::PlatformData pd;
//   // pd.nwh = glfwGetWin32Window(window); //for win
//   // pd.nwh = glfwGetCocoaWindow(window); //for macos
//   // bgfx::setPlatformData(pd);
//
//   bgfx::Init bgfxInit;
//   bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a
//   renderer. bgfxInit.resolution.width = 800; bgfxInit.resolution.height =
//   600; bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
//   // bgfxInit.platformData.nwh = glfwGetWin32Window(window);
//   bgfxInit.platformData.nwh = glfwGetCocoaWindow(window);
//   // bgfxInit.platformData.nwh =
//   // entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
//   // bgfxInit.platformData.ndt = entry::getNativeDisplayHandle();
//   // bgfxInit.platformData.type = entry::getNativeWindowHandleType();
//   bgfx::init(bgfxInit);
//
//   // Enable debug text.
//   bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);
//
//   // Set view rectangle for 0th view
//   bgfx::setViewRect(0, 0, 0, uint16_t(800), uint16_t(600));
//
//   // Clear the view rect
//   bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//   0x303030ff, 1.0f,
//                      0);
//
//   // Set empty primitive on screen
//   bgfx::touch(0);
//
//   while (!glfwWindowShouldClose(window)) {
//     glfwSwapBuffers(window);
//     glfwPollEvents();
//
//     bgfx::frame();
//   }
//
//   /* Clean Up */
//   // glfw
//   glfwDestroyWindow(window);
//   glfwTerminate();
//   // bgfx
//   bgfx::shutdown();
//
//   return 0;
// }
