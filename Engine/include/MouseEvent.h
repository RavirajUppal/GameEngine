#pragma once

#include "Event.h"

namespace RealEngine {

    class REALENGINE_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        GET_EVENT_CATEGORY(EventCategory::Input | EventCategory::Mouse)
        GET_EVENT_TYPE(MouseMoved)

    private:
        float m_MouseX, m_MouseY;
    };

    class REALENGINE_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float x, float y)
            : m_XOffset(x), m_YOffset(y) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }
        GET_EVENT_CATEGORY(EventCategory::Input | EventCategory::Mouse)
        GET_EVENT_TYPE(MouseScrolled)

    private:
        float m_XOffset, m_YOffset;
    };

    class REALENGINE_API MouseButtonEvent : public Event {
    public:
        inline int GetMouseButton() const { return m_Button; }
        GET_EVENT_CATEGORY(EventCategory::Input | EventCategory::Mouse | EventCategory::MouseButton)
    protected:
        MouseButtonEvent(int button)
            : m_Button(button) {}
        int m_Button;
    };

    class REALENGINE_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;;
            return ss.str();
        }
        GET_EVENT_TYPE(MouseButtonPressed)
    };

    class REALENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;;
            return ss.str();
        }
        GET_EVENT_TYPE(MouseButtonReleased)
    };
}