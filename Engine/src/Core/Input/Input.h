#pragma once

#include "Core.h"
#include <utility>

namespace RealEngine
{
    class REALENGINE_API Input
    {
    public:
        static Input* GetInstance() { return m_Instance; }
        static bool IsKeyPressed(int keycode) { return GetInstance()->IsKeyPressedImpl(keycode); }
        static bool IsMouseButtonPressed(int button) { return GetInstance()->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePosition() { return GetInstance()->GetMousePositionImpl(); }
        static float GetMouseX() { return GetInstance()->GetMouseXImpl(); }
        static float GetMouseY() { return GetInstance()->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Input *m_Instance;
    };
}