#pragma once

#include "Events/Event.h"

namespace RealEngine {

    class REALENGINE_API WindowEvent : public Event {
    public:
        GET_EVENT_CATEGORY(EventCategory::Application)
    };

    class REALENGINE_API WindowResizeEvent : public WindowEvent {
    public:
        WindowResizeEvent(int width, int height)
            : m_Width(width), m_Height(height) {}

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        GET_EVENT_TYPE(WindowResize)

    private:
        int m_Width, m_Height;
    };

    class REALENGINE_API WindowCloseEvent : public WindowEvent {
    public:
        GET_EVENT_TYPE(WindowClose)
    };

    class REALENGINE_API WindowFocusEvent : public WindowEvent {
    public:
        GET_EVENT_TYPE(WindowFocus)
    };

    class REALENGINE_API WindowLostFocusEvent : public WindowEvent {
    public:
        GET_EVENT_TYPE(WindowLostFocus)
    };

    class REALENGINE_API WindowMovedEvent : public WindowEvent {
    public:
        GET_EVENT_TYPE(WindowMoved)
    };
}