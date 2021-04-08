#pragma once


/* Entry Point called by Client
   and header files needed by client
 */


#include "core/Application.hpp"
#include "core/Log.hpp"


// extern Engine::Application* Engine::CreateApplication(); 
/* Somewhere an Engine Application pointer.
 Extern is declared in app header but defined in client
*/

int main(int argc, char** argv)
{
    Engine::Log::Init();
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    
}

/* extern : don't rename name of object's functions. Names in extrnal objects could have been mangled due to c++ overloading */
/* objects can be checked in terminal with nm <object> */

/*
As opposed to Sandbox having main with run and delete, sandbox only calls create, engine handles the rest
     int main(){

       Sandbox* sandbox = new Sandbox();
       sandbox->Run();
       delete sandbox; 

       return 0;
     }

1) creates application by calling CreateApplication in Sandbox
2) main calls the run function 
3) main deletes application 

*/