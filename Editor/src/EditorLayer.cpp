#include "EditorLayer.h"


namespace RealEngine
{
    EditorLayer::EditorLayer()
        : Layer("Example"), cameraController(1280.0f / 720.0f)
    {
         auto shader = shaderLib.Load("Default", SHADER_DIR "Default.vert", SHADER_DIR "Default.frag");
        
        float vertices[4 * 9] ={
            -0.5f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
            0.5f, 0.5, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   1.0f, 1.0f,
            -0.5f, 0.5, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 1.0f
        };

        vao = (VertexArray::Create());

        vbo = (VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Vec3, "a_Position"},
            {ShaderDataType::Vec4, "a_Color"},
            {ShaderDataType::Vec2, "a_TexCoord"}
        };
        vbo->SetLayout(layout);

        uint32_t indices[] = {0, 1, 2, 0, 2, 3};
        ibo = (IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
        
        vao->AddVertexBuffer(vbo);
        vao->SetIndexBuffer(ibo);
        shader->Bind();
        shader->SetInt1("u_Texture", 0);
        texture = (Texture2D::Create(TEXTURE_DIR "planks.png"));
        newTexture = Texture2D::Create(TEXTURE_DIR "brick.png");
        Renderer::Init();
        FramebufferSpecification spec;
        spec.Attachments = FramebufferAttachment({FramebufferTexture(FramebufferTextureFormat::RGBA8)});
        spec.Width = Application::Get().GetWindow().GetWidth();
        spec.Height = Application::Get().GetWindow().GetHeight();
        framebuffer = Framebuffer::Create(spec);
    }

    void EditorLayer::OnAttach()
    {
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(TimeStep delta)
    {
        // LOG_INFO("EditorLayer::Update");
        cameraController.OnUpdate(delta);
        framebuffer->Bind();
        RenderCommand::SetClearColor({0.3f, 0.4f, 0.5f, 1.0f});
        RenderCommand::Clear();

        // Renderer::BeginScene(cameraController.GetCamera());
        // shaderLib.Get("Default")->Bind();
        // texture->Bind();
        // Renderer::Submit(shaderLib.Get("Default"), vao);
        // Renderer::EndScene();
        static float rotation = 0.0f;
        rotation += delta * 50;
        if(rotation > 360)
            rotation = 0.0f;

        Renderer2D::BeginScene(cameraController.GetCamera());
        Renderer2D::DrawQuad({0.0f, 0.0f}, {5.0f, 5.0f}, newTexture, 10.0f);
        Renderer2D::DrawRotatedQuad({-0.5f, 0.0f}, {0.4f, 0.4f}, rotation, texture);
        Renderer2D::DrawQuad({0.5f, 0.5f}, {0.2f, 0.2f}, {0.3f, 0.4f, 0.8f, 1.0f});
        Renderer2D::DrawQuad({0.5f, -0.5f}, {0.2f, 0.2f}, {0.8f, 0.4f, 0.6f, 1.0f});

        Renderer2D::EndScene();
        framebuffer->Unbind();

    }

    void EditorLayer::OnImGuiRender()
    {
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.


        static bool dockOpen = true;
        static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    // REMINDER: THIS IS A DEMO FOR ADVANCED USAGE OF DockSpace()!
    // MOST REGULAR APPLICATIONS WILL SIMPLY WANT TO CALL DockSpaceOverViewport(). READ COMMENTS ABOVE.
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        // ShowDockingDisabledMessage();
        LOG_ERROR("docking disabled");
    }

    // Show demo options and help
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if(ImGui::MenuItem("Exit")) { Application::Get().Close(); }
            
            ImGui::EndMenu();
        }
        
        ImGui::EndMenuBar();
    }

            static bool show_demo_window = true;
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
            ImGui::Begin("Viewport");  
            ImVec2 area = ImGui::GetContentRegionAvail();
            if(area.x != framebuffer->GetSpecification().Width || area.y != framebuffer->GetSpecification().Height){
                framebuffer->Resize(area.x, area.y);
            }
            uint32_t texId = framebuffer->GetColorAttachmentRendererID(0);
            ImGui::Image((ImTextureID)(intptr_t)texId, ImVec2(area.x, area.y));

            ImGui::End();
            ImGui::PopStyleVar();
            ImGui::End();
    }

    void EditorLayer::OnEvent(Event& event)
    {
        cameraController.OnEvent(event);
    }
}