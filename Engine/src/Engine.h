#pragma once

/*
Header files used by client
*/
#include "core/Application.hpp"
#include "core/Log.hpp"

/* Entry Point called by Client */

// #include "core/EntryPoint. h"

// extern Engine::Application* Engine::CreateApplication(); 
/* Somewhere an Engine Application pointer.
 Extern is declared in app header but defined in client
*/

int main(int argc, char** argv)
{

    Engine::Log::Init();
    Engine::Log::GetCoreLogger()->warn("Initialized Log!");
    Engine::Log::GetClientLogger()->info("Initialized Log!");

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}


/* Entry Point */

/* extern : don't name name of object's functions. Names in extrnal objects could have been mangled due to c++ overloading */
/* objects can be checked in terminal with nm <object> */

/*
As opposed to Sandbox having main with run and delete, sandbox only calls create, engine handles the rest
     int main(){

       Sandbox* sandbox = new Sandbox();
       sandbox->Run();
       delete sandbox; 

       return 0;
     }
*/