#pragma once

extern Engine::Application* Engine::CreateApplication(); //Extern is called somewhere else, in sandbox app

int main(int argc, char** argv)
{
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}

/*
1) creates application by calling CreateApplication in Sandbox
2) main calls the run function 
3) main deletes application 



As opposed to Sandbox having main with run and delete, sandbox only calls create, engine handles the rest
     int main(){

       Sandbox* sandbox = new Sandbox();
       sandbox->Run();
       delete sandbox; 

       return 0;

     }
*/