#pragma once

#include "Core.h"
#include "RenderCommand.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace RealEngine {

    class REALENGINE_API Renderer {
    public:
        static void Init();
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static void OnWindowResize(uint32_t width, uint32_t height);
        static void EndScene();
        static void Shutdown();
        
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData{
            glm::mat4 ViewProjectionMatrix;
        };
        static std::unique_ptr<SceneData> m_SceneData;
    };
}   