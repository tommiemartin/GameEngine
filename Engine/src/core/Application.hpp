#pragma once

#include "Platform/Window.hpp"
#include "Events/ApplicationEvent.hpp"

namespace Engine {
   
    class Application
    {
      public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& e);

        private:
          std::unique_ptr<Window> m_Window; //unique ptr, only for this class
          bool m_running = true;

          bool OnWindowClose(WindowCloseEvent& e);

    };

    // declared but defined in Client
    Application* CreateApplication();
 
}//namespace