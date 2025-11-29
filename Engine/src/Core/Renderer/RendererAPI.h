#pragma once

#include <glm/glm.hpp>
#include "Core.h"
#include "VertexArray.h"

namespace RealEngine
{
    class REALENGINE_API RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1,
            Direct3D11 = 2,
            Direct3D12 = 3,
            Vulkan = 4,
            Metal = 5
        };

    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };

}