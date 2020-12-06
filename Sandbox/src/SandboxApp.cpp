#include <Engine.h> // path is included so you don't need relative path


class Sandbox : public Engine::Application {
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Engine::Application* Engine::CreateApplication(){
    return new Sandbox();
}

