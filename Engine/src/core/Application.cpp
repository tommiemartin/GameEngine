#include "Application.hpp"

//temp
#include "../Events/ApplicationEvent.hpp"
#include "../core/Log.hpp"

namespace Engine{

    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280,720);
        ENGINE_TRACE(e);

        while(true);
    }


}