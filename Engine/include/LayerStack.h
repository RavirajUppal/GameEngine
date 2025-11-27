#pragma once

#include "Core.h"
#include "Layer.h"

namespace RealEngine {

    using LayerVec = std::vector<Layer*>;

    class REALENGINE_API LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        LayerVec::iterator begin() { return m_Layers.begin(); }
        LayerVec::iterator end() { return m_Layers.end(); }
    private:
        LayerVec m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

}