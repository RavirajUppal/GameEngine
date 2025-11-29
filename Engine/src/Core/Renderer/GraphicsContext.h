#pragma once

#include "Core.h"

namespace RealEngine
{
    class GraphicsContext{
        public:
            ~GraphicsContext() = default;
            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}