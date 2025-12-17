#include "VertexArray.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace RealEngine{
    std::shared_ptr<VertexArray> VertexArray::Create(){
        switch(RendererAPI::GetAPI()){
            case RendererAPI::API::None :
            case RendererAPI::API::Direct3D11 :
            case RendererAPI::API::Direct3D12 :
            case RendererAPI::API::Vulkan :
            case RendererAPI::API::Metal :
                REALENGINE_ASSERT(false, "RendererAPI is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
        }
        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}