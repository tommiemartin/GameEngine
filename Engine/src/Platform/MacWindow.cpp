#include "MacWindow.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"


namespace Engine{
    static bool s_GLFWInitialized = false; // once per Engine

    static void GLFWErrorCallback(int error, const char* description){
        ENGINE_ERROR("GLFW ERROR ({0}): {1}",error, description);
    }

    Window* Window::Create(const WindowProps& props){
        return new MacWindow(props); //Definition for Mac from windows class, calls constuctor which calls init
    }

    MacWindow::MacWindow(const WindowProps& props){
        Init(props);
    }

    MacWindow::~MacWindow(){
        Shutdown();
    }

    void MacWindow::Init(const WindowProps& props){
        m_Data.Title  = props.Title;
        m_Data.Width  = props.Width;
        m_Data.Height = props.Height;

        ENGINE_INFO("Creating window {0} ({1}, {2})",props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized){ //only initialized once regarless of number of windows
            int success = glfwInit();

            //ADD ASSERT  <-- asserts added 20:53
            // ENGINE_ERROR(success," Could not initialize GLFW"); 

            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized= true;
        }

        m_Window = glfwCreateWindow( (int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set GLFW Callbacks, take in the m_Window context and a GLFW callback function passed as a lambda
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            
            // glfwGetWindowUserPointer(window); //returns a void pointer, must be cast to our window data
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 
            data.Width  = width;
            data.Height = height;

            WindowResizeEvent event(width, height); // create window resize event
            data.EventCallback(event); //dispatch event
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 
            WindowCloseEvent event;
            data.EventCallback(event); 
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key,0);
                    data.EventCallback(event);
                    break;
                } 
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,1);
                    data.EventCallback(event);
                    break;
                }
            }//switch

        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }            
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        }); 

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

    }//Init

    void MacWindow::Shutdown(){
        glfwDestroyWindow(m_Window);
    }

    void MacWindow::OnUpdate(){
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void MacWindow::SetVSync(bool enabled){
        if(enabled)
            glfwSwapInterval(1); //1 frame before swap
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled; //can't retrieve from glfw so stored in Window class 
    }

    bool MacWindow::IsVSync() const{
        return m_Data.VSync;
    }

}//