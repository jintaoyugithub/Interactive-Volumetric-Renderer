#include "LLGL/Utils/VertexFormat.h"
#include <LLGL/LLGL.h>
#include <exception>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main() {
  try {
    // Vertex data structure
    struct Vertex {
      float position[2];
      uint8_t color[4];
    };
    // Vertex data (3 vertices for our triangle)
    Vertex vertices[] = {
        {{0.0f, 0.5f}, {255, 0, 0, 255}},
        {{0.5f, -1.0f}, {0, 255, 0, 255}},
        {{-0.5f, -1.0f}, {0, 0, 255, 255}},
    };

    // create a llgl renderer instance
    LLGL::RenderSystemPtr renderer = LLGL::RenderSystem::Load("OpenGL");
    // create framebuffer
    LLGL::SwapChainDescriptor swapChainDesc;
    { swapChainDesc.resolution = {640, 480}; }
    LLGL::SwapChain *swapChain = renderer->CreateSwapChain(swapChainDesc);
    // create the window
    LLGL::Window *window = nullptr;
    if (LLGL::IsInstanceOf<LLGL::Window>(swapChain->GetSurface())) {
      window = LLGL::CastTo<LLGL::Window>(&swapChain->GetSurface());
      window->SetTitle(L"LLGL Example: Hello Triangle");
      window->Show();
    }
    // create vertex format
    LLGL::VertexFormat vertexFormat;

    // Append 2D float vector for position attribute
    vertexFormat.AppendAttribute({"position", LLGL::Format::RG32Float});

    // Append 3D unsigned byte vector for color
    vertexFormat.AppendAttribute({"color", LLGL::Format::RGBA8UNorm});

    // Update stride in case out vertex structure is not 4-byte aligned
    vertexFormat.SetStride(sizeof(Vertex));

    // Create vertex buffer
    LLGL::BufferDescriptor vBufferDesc;
    vBufferDesc.size = sizeof(vertices); // Size (in bytes) of the buffer
    vBufferDesc.bindFlags =
        LLGL::BindFlags::VertexBuffer; // Use for vertex buffer binding
    vBufferDesc.vertexAttribs =
        vertexFormat.attributes; // Vertex buffer attributes
    LLGL::Buffer *vertexBuffer = renderer->CreateBuffer(vBufferDesc, vertices);

    // Create shaders
    LLGL::Shader *vertShader = nullptr;
    LLGL::Shader *fragShader = nullptr;

    const auto &languages = renderer->GetRenderingCaps().shadingLanguages;

    // create shader descriptor
    LLGL::ShaderDescriptor vsDesc;
    vsDesc.type = LLGL::ShaderType::Vertex;
    vsDesc.source = "default.vs";
    vsDesc.sourceType = LLGL::ShaderSourceType::CodeFile;
    // specific for vertex shader
    vsDesc.vertex.inputAttribs = vertexFormat.attributes;

    LLGL::ShaderDescriptor fsDesc;
    fsDesc.type = LLGL::ShaderType::Fragment;
    fsDesc.source = "default.fs";
    fsDesc.sourceType = LLGL::ShaderSourceType::CodeFile;

    vertShader = renderer->CreateShader(vsDesc);
    fragShader = renderer->CreateShader(fsDesc);

    for (LLGL::Shader *shader : {vertShader, fragShader}) {
      if (const LLGL::Report *report = shader->GetReport())
        LLGL::Log::Errorf("%s", report->GetText());
    }

    // Create graphics pipeline
    LLGL::GraphicsPipelineDescriptor gpDesc;
    gpDesc.vertexShader = vertShader;
    gpDesc.fragmentShader = fragShader;
    gpDesc.renderPass = swapChain->GetRenderPass();
    LLGL::PipelineState *pipeline = renderer->CreatePipelineState(gpDesc);
    // Create command buffer to submit subsequent graphics commands to the GPU
    LLGL::CommandBuffer *commands = renderer->CreateCommandBuffer();

    const float bgColor[4] = {0.7f, 0.1f, 0.4f, 1.0f};

    // render loop
    while (window->ProcessEvents()) {
      // Begin recording commands
      commands->Begin();
      {
        // Set viewport and scissor rectangle
        commands->SetViewport(swapChain->GetResolution());

        // Set vertex buffer
        commands->SetVertexBuffer(*vertexBuffer);

        // Set the swap-chain as the initial render target
        commands->BeginRenderPass(*swapChain);
        {
          // Clear color buffer
          commands->Clear(LLGL::ClearFlags::Color, bgColor);

          // Set graphics pipeline
          commands->SetPipelineState(*pipeline);

          // Draw triangle with 3 vertices
          commands->Draw(3, 0);
        }
        commands->EndRenderPass();
      }
      commands->End();

      // Present the result on the screen
      swapChain->Present();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
