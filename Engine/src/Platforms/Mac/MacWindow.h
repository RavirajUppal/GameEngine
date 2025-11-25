#pragma once

#include "Window.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace RealEngine {

    class MacWindow : public Window {
    public:
        MacWindow(const WindowProperties& props);
        virtual ~MacWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override { return m_Data.VSync; }

    private:
        virtual void SetWindowCallbacks();
        virtual void Shutdown();

        GLFWwindow* m_Window;
        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

}