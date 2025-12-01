#pragma once

#include "Core.h"
#include <sstream>

namespace RealEngine {
    
    #define GET_EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }
    
    #define GET_EVENT_CATEGORY(category) virtual int GetCategoryFlags() const override { return static_cast<int>(category); }
    
    
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    
    enum class EventCategory {
        None = 0,
        Application = 1 << 0,
        Input       = 1 << 1,
        Keyboard    = 1 << 2,
        Mouse       = 1 << 3,
        MouseButton = 1 << 4
    };
    
    inline EventCategory operator|(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }
    
    class REALENGINE_API Event {
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & static_cast<int>(category);
        }
        bool m_Handled = false;
    };

    class EventDispatcher {
        // template<typename T>
        // using func = std::function<bool(Event&)>;
        public:
        EventDispatcher(Event& event)
            : m_Event(event) {}
        
        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
        
        private:
        Event& m_Event;
    };

    // inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    //     return os << e.ToString();
    // }
}