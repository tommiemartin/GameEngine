#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


#include <memory> //to use shared pointers

namespace Engine{

    class Log{
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   {return s_CoreLogger;   }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
    
} // namespace Engine

/* 
static shared pointers to spd:logger returned by reference

*/