#include "Renderer/Framebuffer.h"
#include "Renderer/RendererAPI.h"
#include "Platforms/OpenGL/OpenGLFramebuffer.h"

namespace RealEngine
{
    std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch(RendererAPI::GetAPI()){
            case RendererAPI::API::None :
            case RendererAPI::API::Direct3D11 :
            case RendererAPI::API::Direct3D12 :
            case RendererAPI::API::Vulkan :
            case RendererAPI::API::Metal :
                REALENGINE_ASSERT(false, "RendererAPI is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLFramebuffer>(spec);
        }
        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
