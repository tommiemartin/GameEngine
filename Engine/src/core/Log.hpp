#pragma once
#include "PCH.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h> //output stream operator for custom types like events



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

// static shared pointers to spd:logger returned by reference
 
// log macros, (...) variable number of arguments, forwards arguments from macro to __VA_ARGS__ in function
#define ENGINE_TRACE(...)       ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...)        ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define ENGINE_WARN(...)        ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__) 
#define ENGINE_ERROR(...)       ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__) 
#define ENGINE_CRITICAL(...)    ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...)       ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...)        ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...)        ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)       ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...)    ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)

// for dist builds define as nothing
// #define ENGINE_INFO