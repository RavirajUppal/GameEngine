#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logging/Log.h"

namespace RealEngine
{
    OpenGLContext::OpenGLContext(GLFWwindow *window)
        :m_Windowhandle(window)
    {
        REALENGINE_ASSERT(m_Windowhandle, "Window Handle is NULL!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Windowhandle);
        auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        REALENGINE_ASSERT(success, "Could not load glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Windowhandle);
    }
}