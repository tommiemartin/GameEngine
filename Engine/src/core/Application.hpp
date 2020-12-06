#pragma once

#include "Core.hpp"

namespace Engine {
   
    // class ENGINE_API Application
    class Application
    {
      public:
            Application();
            virtual ~Application();

            void Run();

    };

    // declared but defined in Client
    Application* CreateApplication();
 
}//namespace