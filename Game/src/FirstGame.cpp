#include"RealEngine.h"

class ExampleLayer : public RealEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // LOG_INFO("ExampleLayer::Update");
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