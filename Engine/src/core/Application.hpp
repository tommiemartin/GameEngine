#pragma once

namespace Engine {
   
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