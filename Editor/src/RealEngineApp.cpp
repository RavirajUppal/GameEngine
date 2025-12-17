#include "EditorLayer.h"
#include "EntryPoint.h"


namespace RealEngine
{
    class RealEngineApp : public Application
    {
    public:
        RealEngineApp()
        {
            LOG_INFO("RealEngineApp Constructor");
            PushLayer(new EditorLayer());
        }

        ~RealEngineApp()
        {
            LOG_INFO("RealEngineApp Destroyed");
        }

        void Run() override
        {
            Application::Run();

            LOG_INFO("RealEngineApp Running");
        }
    };

    Application *CreateApplication()
    {
        LOG_INFO("RealEngineApp creating");

        return new RealEngineApp();
    }
}