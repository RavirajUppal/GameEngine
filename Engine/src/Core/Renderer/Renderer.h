#pragma once

#include "Core.h"
#include "RenderCommand.h"

namespace RealEngine {

    class REALENGINE_API Renderer {
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
    };
}   