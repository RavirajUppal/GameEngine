#include "Texture.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

namespace RealEngine
{
    Texture2D *Texture2D::Create(const char *path)
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
                return new OpenGLTexture(path);
        }
        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
