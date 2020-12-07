#include <Engine.h> // path is included in 'c_cpp_properties' so you can use <>, don't need relative path

class Sandbox : public Engine::Application {
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

//Definintion!! declared in app.hpp
// An instanced sandbox is just an instance of the application class
Engine::Application* Engine::CreateApplication(){
    return new Sandbox();
} 

