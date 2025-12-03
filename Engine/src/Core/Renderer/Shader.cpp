#include "Shader.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace RealEngine
{
    std::shared_ptr<Shader> Shader::Create(const std::string& name, std::string_view vertexFilePath, std::string_view fragmentFilePath, std::string_view geometryFilePath){
        switch(RendererAPI::GetAPI()){
            case RendererAPI::API::None :
            case RendererAPI::API::Direct3D11 :
            case RendererAPI::API::Direct3D12 :
            case RendererAPI::API::Vulkan :
            case RendererAPI::API::Metal :
                REALENGINE_ASSERT(false, "RendererAPI is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLShader>(name, vertexFilePath, fragmentFilePath, geometryFilePath);
        }
        REALENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader> &shader)
    {
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const std::shared_ptr<Shader> &shader)
    {
        const std::string& name = shader->GetName();
        REALENGINE_ASSERT(!Exist(name), "Shader already exists!!");
        m_Shaders[name] = shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, std::string_view vertexFilePath, std::string_view fragmentFilePath, std::string_view geometryFilePath)
    {
        // REALENGINE_ASSERT(!Exist(name), "Shader already exists!!");
        std::shared_ptr<Shader> shader = Shader::Create(name, vertexFilePath, fragmentFilePath, geometryFilePath);
        ShaderLibrary::Add(name, shader);
        return m_Shaders[name];
    }

    std::shared_ptr<Shader> ShaderLibrary::Get(const std::string &name)
    {
        REALENGINE_ASSERT(Exist(name), "Shader does not exist!!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exist(const std::string &name)
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}