#pragma once
#include "PCH.hpp"

#include "Events/Event.hpp" 
#include "core/Log.hpp"

// Abtract Windows class for various platforms

namespace Engine{

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& t = "Game Engine",
                    unsigned int w  = 1280,
                    unsigned int h = 780)
            : Title(t), Width(w), Height(h) {}
    };

    class Window{
        public:
            using EventCallbackFn = std::function<void(Event&)>; // symbol becomes std::function that takes in a Event& and returns void
            //std::function, function itself can be different

            virtual ~Window() {}

            virtual void OnUpdate() = 0;
            
            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;

            //Window attributes
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            // virtual void* GetNativeWindow() const = 0;

            // Create is implmented per platform
            // declared here, defined in each platform cpp, mac, windows, etc
            static Window* Create(const WindowProps& props = WindowProps());

    };

}//