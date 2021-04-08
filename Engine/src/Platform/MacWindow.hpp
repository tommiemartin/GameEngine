#pragma once

#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace Engine {

    class MacWindow : public Window{
    public:
        MacWindow(const WindowProps& props);
        virtual ~MacWindow();

        void OnUpdate() override; //updates GLFW 1 per frame

        inline unsigned int GetWidth()  const override{ return m_Data.Width; }
        inline unsigned int GetHeight() const override{ return m_Data.Height; }

        //attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override {m_Data.EventCallback = callback;}
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        // inline virtual void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;

        // GranphicsContext* m_Context;

        struct WindowData //passed to GLFW during event callbacks instead of passing entire class
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}//

