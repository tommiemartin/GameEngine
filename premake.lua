workspace "GameEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

-- ex) debug , windows, x64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name")
    -- for intermediates 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name")

    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}vendor/vendor/spdlog/include"
    }

    -- platform specific properties
    filter "system:windows"
        cppdialect "C++17"
        statticruntime "On"
        systemversion "Latest"

        defines
        {
            "DLLs go here",
            "DLLs go here"
        }

        -- copy into build folder
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath ../bin" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        optimize "On"
    
    filter "configurations:Release"
        defines "ENGINE_DEBUG"
        optimize "On"
    
    filter "configurations:Distribution"
        defines "ENGINE_DEBUG"
        optimize "On"

---------------- Sandbox ------------

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"


        --etc etc