#include "MacWindow.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "Log.h"

namespace RealEngine
{
    static bool s_GLFWInitialized = false;
    Window* Window::Create(WindowProperties props)
    {
        return new MacWindow(props);
    }

    MacWindow::MacWindow(const WindowProperties& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        
        LOG_CORE_INFO("Creating window {0} ({1}, {2})");
        
        if(!s_GLFWInitialized){
            int success = glfwInit();
            REALENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback([](int error, const char* description){
                LOG_CORE_ERROR("GLFW Error ({0}): {1}");
            });
            s_GLFWInitialized = true;
        }
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
        }
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        SetWindowCallbacks();
    }

    MacWindow::~MacWindow()
    {
        Shutdown();
    }

    void MacWindow::OnUpdate()
    {
        glClearColor(0.5f, 0.5f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
    
    void MacWindow::SetWindowCallbacks()
    {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action){
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action){
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }
    
    void MacWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }
    
    void MacWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
}
