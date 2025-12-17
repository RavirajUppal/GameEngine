#pragma once

#include "RealEngine.h"

namespace RealEngine
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(TimeStep delta) override;
        void OnImGuiRender() override;
        void OnEvent(Event &event) override;

    private:
        ShaderLibrary shaderLib;
        OrthographicCameraController cameraController;
        std::shared_ptr<Texture2D> texture;

        std::shared_ptr<Framebuffer> framebuffer;
        std::shared_ptr<VertexArray> vao;
        std::shared_ptr<VertexBuffer> vbo;
        std::shared_ptr<IndexBuffer> ibo;

        std::shared_ptr<Texture2D> newTexture;
    };
}