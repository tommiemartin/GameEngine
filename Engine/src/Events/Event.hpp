#pragma once

// move to precompiled headers 
#include <string>
#include <functional>

#define BIT(x) (1 << x)

namespace Engine {
    /*** Events ***
     * Engine events are currently blocking. When an event occurs it get dispatched must be dealt with right then
     * a better strategy might be to buffer events and process them in the update stage
     ***/

    enum class EventType{ //returned by EVENT_CLASS_TYPE macro
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, 
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    //for filtering before looking at specific types, can be set to multiple bits and masked out
    enum EventCategory{ //returned by EVENT_CLASS_CATEGORY macro
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };

/*
Macros finds type and replaces it where needed, 
*/

// creates these 3 functions with the given type for any child of event
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
                                                                virtual EventType GetEventType() const override {return GetStaticType(); }\
                                                                virtual const char* GetName() const override { return #type; }

/*  
static  EventType GetStaticType() {return EventType::##type; }  <-- static, type can be known without instancing. ## macro operator creates 1 token by pasting 2 together
virtual EventType GetEventType() const override {return GetStaticType(); } <--  instanced version?? Appears to return the same thing
virtual const char* GetName() const override { return #type; } <-- # macro operator puts quotes around token
*/


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    class Event
    {
    friend class EventDispatcher;
    public: //pure virtual every event must implement themm
        virtual EventType   GetEventType()       const = 0;
        virtual const char* GetName()            const = 0; //debug only
        virtual int         GetCategoryFlags()   const = 0;
        virtual std::string ToString()           const {return GetName();} //debug only, overridden in children to provide additional data

        inline bool IsInCategory(EventCategory category){
            return GetCategoryFlags() & category;
            //TODO why the & here 
        }
    protected:
        bool m_handled = false;

    };

    class EventDispatcher // 26:00 
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {

        }
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if(m_Event.GetEventType() == T::GetStaticType() ) // TODO ???
            {
                m_Event.m_handled = func( *(T*)&m_Event );
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {//allows events to be pushed to outpust stream   
        return os << e.ToString();
    }
}//