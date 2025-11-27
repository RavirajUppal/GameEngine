#pragma once

#include "Event.h"

namespace RealEngine {

    class REALENGINE_API KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }
        GET_EVENT_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode) {}
    
        int m_KeyCode;
    };

    class REALENGINE_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        inline int GetRepeatCount() const { return m_RepeatCount; }
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }
        GET_EVENT_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    class REALENGINE_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
        GET_EVENT_TYPE(KeyReleased)
    };
}