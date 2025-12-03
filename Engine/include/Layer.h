#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "TimeStep.h"

namespace RealEngine {

    class REALENGINE_API Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(TimeStep delta) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_Name; }
    protected:
        std::string m_Name;
    };

}