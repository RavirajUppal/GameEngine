#include"RealEngine.h"

class ExampleLayer : public RealEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), cameraController(1280.0f / 720.0f)
    {
         auto shader = shaderLib.Load("Default", SHADER_DIR "Default.vert", SHADER_DIR "Default.frag");
        
        float vertices[4 * 9] ={
            -0.5f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
            0.5f, 0.5, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   1.0f, 1.0f,
            -0.5f, 0.5, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 1.0f
        };

        vao.reset(RealEngine::VertexArray::Create());

        vbo.reset(RealEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

        RealEngine::BufferLayout layout = {
            {RealEngine::ShaderDataType::Vec3, "a_Position"},
            {RealEngine::ShaderDataType::Vec4, "a_Color"},
            {RealEngine::ShaderDataType::Vec2, "a_TexCoord"}
        };
        vbo->SetLayout(layout);

        uint32_t indices[] = {0, 1, 2, 0, 2, 3};
        ibo.reset(RealEngine::IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
        
        vao->AddVertexBuffer(vbo);
        vao->SetIndexBuffer(ibo);
        shader->Bind();
        shader->SetInt1("u_Texture", 0);
        texture.reset(RealEngine::Texture2D::Create(TEXTURE_DIR "brick.png"));
    }

    void OnUpdate(RealEngine::TimeStep delta) override
    {
        // LOG_INFO("ExampleLayer::Update");
        cameraController.OnUpdate(delta);

        RealEngine::RenderCommand::SetClearColor({0.3f, 0.4f, 0.5f, 1.0f});
        RealEngine::RenderCommand::Clear();

        RealEngine::Renderer::BeginScene(cameraController.GetCamera());

        shaderLib.Get("Default")->Bind();
        texture->Bind();
        RealEngine::Renderer::Submit(shaderLib.Get("Default"), vao);

        RealEngine::Renderer::EndScene();

    }

    void OnImGuiRender() override
    {
        static bool show_demo_window = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some not very useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::End();
        }
    }

    void OnEvent(RealEngine::Event& event) override
    {
        cameraController.OnEvent(event);
    }

    private:
        RealEngine::ShaderLibrary shaderLib;
        // std::shared_ptr<Shader> shader;
        RealEngine::OrthographicCameraController cameraController;
        std::shared_ptr<RealEngine::Texture> texture;

        std::shared_ptr<RealEngine::VertexArray> vao;
        std::shared_ptr<RealEngine::VertexBuffer> vbo;
        std::shared_ptr<RealEngine::IndexBuffer> ibo;
};

class FirstGame : public RealEngine::Application
{
public:
    FirstGame()
    {
        LOG_INFO("FirstGame Constructor");
        PushLayer(new ExampleLayer());
    }

    ~FirstGame()
    {
        LOG_INFO("FirstGame Destroyed");
    }

    void Run() override
    {
        RealEngine::Application::Run();

        LOG_INFO("FirstGame Running");
    }

};

RealEngine::Application* RealEngine::CreateApplication()
{
    LOG_INFO("FirstGame creating");
    
    return new FirstGame();
}