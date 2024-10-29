-- premake5.lua
workspace "MisakaProjects"
    architecture "x64"
    startproject "Sandbox"
    
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- vcpkg directories for includes and libraries
VCPKG_DIR = "vcpkg_installed/x64-windows-static"
VCPKG_INCLUDE = VCPKG_DIR .. "/include"
VCPKG_LIB = VCPKG_DIR .. "/lib"
VCPKG_DEBUG_LIB = VCPKG_DIR .. "/debug/lib"

-- Assets Project
project "Assets"
    location "Assets"
    kind "None"
    language "C++"
    
    files
    {
        -- models
        "%{prj.location}/**.obj",
        -- shaders
        "%{prj.location}/**.vert",
        "%{prj.location}/**.frag",
    }


-- Core Project
project "Core"
    location "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("on")
    scanformoduledependencies "true"

    buildoptions { "/utf-8" }  -- 使用 UTF-8 编码

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    
    files
    {
        -- Automatically include all .hpp(.h) and .cpp files in each module folder
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.ixx"
    }

    includedirs
    {
        -- Add the vcpkg include path
        "%{wks.location}/Core",  -- Include the Core project modules
        VCPKG_INCLUDE
    }

    libdirs 
    {
        -- Add the vcpkg library path
        VCPKG_DEBUG_LIB
    }
    
    links
    {
        "assimp-vc143-mtd",
        "draco",
        "glad",
        "glfw3",
        "glm",
        "imguid",
        "kubazip",
        "minizip",
        "poly2tri",
        "polyclipping",
        "pugixml",
        "zlibd",
    }

    -- 添加 /NODEFAULTLIB:library 选项来避免默认库的链接冲突
    buildoptions { "/NODEFAULTLIB:MSVCRT" }  -- 如果是其他库的冲突，请替换 'MSVCRT' 为相应的库名
    
    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "CORE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CORE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CORE_RELEASE"
        runtime "Release"
        optimize "on"

-- Sandbox Project
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("on")
    scanformoduledependencies "true"

    buildoptions { "/utf-8" }  -- 使用 UTF-8 编码
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.h",
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.ixx"
    }
    
    includedirs
    {
        "%{wks.location}/Core",  -- Include the Core project modules
        VCPKG_INCLUDE  -- Include vcpkg dependencies
    }

    links
    {
        "Core"   -- Link with Core library
    }

    -- 添加 /NODEFAULTLIB:library 选项来避免默认库的链接冲突
    buildoptions { "/NODEFAULTLIB:MSVCRT" }  -- 如果是其他库的冲突，请替换 'MSVCRT' 为相应的库名

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "SANDBOX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SANDBOX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SANDBOX_RELEASE"
        runtime "Release"
        optimize "on"
