#include "Shader.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace RealEngine
{
    Shader* Shader::Create(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath){
        switch(RendererAPI::GetAPI()){
            case RendererAPI::API::None :
            case RendererAPI::API::Direct3D11 :
            case RendererAPI::API::Direct3D12 :
            case RendererAPI::API::Vulkan :
            case RendererAPI::API::Metal :
                REALENGINE_ASSERT(false, "RendererAPI is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexFilePath, fragmentFilePath, geometryFilePath);
        }
        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}