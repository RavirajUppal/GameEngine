#pragma once

#include "Layer.h"

namespace RealEngine {

    class REALENGINE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        void OnEvent(Event &event) override;
        void SetBlockEvents(bool block) { m_BlockEvents = block; }
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
        bool m_BlockEvents = false;
    };
}