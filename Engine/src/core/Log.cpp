#include "Log.hpp"

// translation unit: source file after preprocessor

namespace Engine{

        //static functions in init so coreLogger vars must be static and revealed by declaration here

        std::shared_ptr<spdlog::logger> Log::s_CoreLogger;  
        std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

        void Log::Init(){
            spdlog::set_pattern("%^[%T] %n: %v%$"); //timestamp, name of logger, message
            s_CoreLogger   = spdlog::stdout_color_mt("ENGINE");
            s_CoreLogger->set_level(spdlog::level::trace);

            s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
            s_ClientLogger->set_level(spdlog::level::trace);
        }
    
} // namespace Engine