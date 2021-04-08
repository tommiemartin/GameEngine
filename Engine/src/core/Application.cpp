#include "Application.hpp"

// #include "../Events/ApplicationEvent.hpp"
// #include "Log.hpp"
#include <GLFW/glfw3.h>

namespace Engine{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application(){
        // window create calls constuctor in platform window which calls init
        m_Window = std::unique_ptr<Window>(Window::Create());  //explicit constructor, use cast

        // m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1) ); // TODO
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    }

    Application::~Application(){
        //unique window pointer does not need to be deleted
    }

    void Application::Run(){
        while(m_running){

            glClearColor(.25,0,.3,.3);
            glClear(GL_COLOR_BUFFER_BIT);
            
            m_Window->OnUpdate(); 

        }
    }

    // NEW //

    void Application::OnEvent(Event& e){

        /*  GLFW window doesnt need to know about Application
            GLFW callbacks send an event to the dispatcher
            event type of the incoming event == to static type of template event calls the corresponding bind function
        */
        EventDispatcher dispatcher(e); //<-- incoming event
        //                       V--static template type       V--function to call if they match
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); 

        ENGINE_INFO("{0}",e);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_running = false;
        return true;
    }


}//