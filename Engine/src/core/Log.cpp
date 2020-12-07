#include "Log.hpp"

// translation unit: source file after preprocessor

namespace Engine{

        std::shared_ptr<spdlog::logger> Log::s_CoreLogger;  // why here if in header?
        std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

        void Log::Init(){
            spdlog::set_pattern("%^[%T] %n: %v%$"); //timestamp, name of logger, message
            s_CoreLogger   = spdlog::stdout_color_mt("ENGINE");
            s_CoreLogger->set_level(spdlog::level::trace);

            s_ClientLogger = spdlog::stdout_color_mt("APP");
            s_ClientLogger->set_level(spdlog::level::trace);
        }
        
} // namespace Engine