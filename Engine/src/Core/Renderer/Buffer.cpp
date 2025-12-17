#include "Renderer/Buffer.h"
#include "Renderer/RendererAPI.h"
#include "Core.h"
#include "Logging/Log.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace RealEngine
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            REALENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
        default:
            // LOG_ERROR("{} RendererAPI is currently not supported!", RendererAPI::GetAPI());
            REALENGINE_ASSERT(false, "Unsupported RendererAPI!");
            return nullptr;
        }

        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            REALENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        default:
            // LOG_ERROR("{} RendererAPI is currently not supported!", RendererAPI::GetAPI());
            REALENGINE_ASSERT(false, "Unsupported RendererAPI!");
            return nullptr;
        }

        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            REALENGINE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, count);
        default:
            // LOG_ERROR("{} RendererAPI is currently not supported!", RendererAPI::GetAPI());
            REALENGINE_ASSERT(false, "Unsupported RendererAPI!");
            return nullptr;
        }

        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}