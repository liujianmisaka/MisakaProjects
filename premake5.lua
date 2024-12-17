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

GLFW_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE .. "/GLFW"
GLAD_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE .. "/glad"
GLM_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE .. "/glm"
ASSIMP_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE .. "/assimp"
ENTT_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE .. "/entt"
IMGUI_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE
TINYXML2_VCPKG_INCLUDE_DIR = VCPKG_INCLUDE

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
        "%{prj.location}/**.sc",
        -- xml
        "%{prj.location}/**.xml",
    }

-- Library Project
project "Library"
    location "Library"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("off")
    scanformoduledependencies "true"

    buildoptions { "/utf-8", "/Zc:__cplusplus", "/Zc:preprocessor" }  -- 使用 UTF-8 编码

    targetdir ("bin/" .. outputdir .. "/Sandbox")
    objdir ("bin-int/" .. outputdir .. "/Sandbox")

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
        GLM_VCPKG_INCLUDE_DIR,
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "LIBRARY_PLATFORM_WINDOWS",
            "BX_CONFIG_DEBUG"
        }

    filter "configurations:Debug"
        defines "LIBRARY_DEBUG"
        runtime "Debug"
        symbols "on"

        -- buildoptions { "/Z7" }

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_DEBUG_LIB
        }

        links
        {
            "glm",
        }

    filter "configurations:Release"
        defines "LIBRARY_RELEASE"
        runtime "Release"
        optimize "on"

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_LIB
        }

        links
        {
            "glm",
        }

-- BehaviorTree Project
project "BehaviorTree"
    location "BehaviorTree"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("off")
    scanformoduledependencies "true"

    buildoptions { "/utf-8", "/Zc:__cplusplus", "/Zc:preprocessor" }  -- 使用 UTF-8 编码

    targetdir ("bin/" .. outputdir .. "/Sandbox")
    objdir ("bin-int/" .. outputdir .. "/Sandbox")

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
        "%{wks.location}/Library",  -- Include the Library project modules
    }

    links
    {
        "Library",
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "BEHAVIORTREE_PLATFORM_WINDOWS",
            "BX_CONFIG_DEBUG"
        }

    filter "configurations:Debug"
        defines "BEHAVIORTREE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BEHAVIORTREE_RELEASE"
        runtime "Release"
        optimize "on"

-- Engine Project
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("off")
    scanformoduledependencies "true"
    
    buildoptions { "/utf-8", "/Zc:__cplusplus", "/Zc:preprocessor" }  -- 使用 UTF-8 编码

    targetdir ("bin/" .. outputdir .. "/Sandbox")
    objdir ("bin-int/" .. outputdir .. "/Sandbox")

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
        GLFW_VCPKG_INCLUDE_DIR,
        GLAD_VCPKG_INCLUDE_DIR,
        GLM_VCPKG_INCLUDE_DIR,
        "%{wks.location}/Library",  -- Include the Library project modules
    }

    links
    {
        "Library",
        "glad",
        "glfw3",
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "ENGINE_PLATFORM_WINDOWS",
            "BX_CONFIG_DEBUG"
        }

    filter "configurations:Debug"
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols "on"

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_DEBUG_LIB
        }

    filter "configurations:Release"
        defines "ENGINE_RELEASE"
        runtime "Release"
        optimize "on"

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_LIB
        }

-- Core Project
project "Core"
    location "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("off")
    scanformoduledependencies "true"

    buildoptions { "/utf-8", "/Zc:__cplusplus", "/Zc:preprocessor" }  -- 使用 UTF-8 编码

    targetdir ("bin/" .. outputdir .. "/Sandbox")
    objdir ("bin-int/" .. outputdir .. "/Sandbox")
    
    
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
        VCPKG_INCLUDE,
        VCPKG_INCLUDE .. "/bx/compat/msvc",
        "%{wks.location}/Library",  -- Include the Library project modules
        "%{wks.location}/BehaviorTree",  -- Include the BehaviorTree project modules
    }
    
    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "CORE_PLATFORM_WINDOWS",
            "BX_CONFIG_DEBUG"
        }

    filter "configurations:Debug"
        defines "CORE_DEBUG"
        runtime "Debug"
        symbols "on"

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_DEBUG_LIB,
        }

        links
        {
            "assimp-vc143-mtd",
            "bgfx",
            "bimg",
            "bimg_decode",
            "bimg_encode",
            "bx",
            "draco",
            "glad",
            "glfw3",
            "imguid",
            "kubazip",
            "minizip",
            "poly2tri",
            "polyclipping",
            "pugixml",
            "squishd",
            "tinyxml2",
            "zlibd",

            "Library",
            "BehaviorTree",
        }

    filter "configurations:Release"
        defines "CORE_RELEASE"
        runtime "Release"
        optimize "on"

        libdirs 
        {
            -- Add the vcpkg library path
            VCPKG_LIB
        }

        links
        {
            "assimp-vc143-mt",
            "bgfx",
            "bimg",
            "bimg_decode",
            "bimg_encode",
            "bx",
            "draco",
            "glad",
            "glfw3",
            "imgui",
            "kubazip",
            "minizip",
            "poly2tri",
            "polyclipping",
            "pugixml",
            "squish",
            "zlib",

            "Library",
            "BehaviorTree",
        }

-- Sandbox Project
project "Sandbox"
    location "Sandbox"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"
    enablemodules("on")
    buildstlmodules("off")
    scanformoduledependencies "true"

    entrypoint "mainCRTStartup"  -- 指定入口点为 mainCRTStartup

    buildoptions { "/utf-8", "/Zc:__cplusplus" }  -- 使用 UTF-8 编码
    
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
        "%{wks.location}/BehaviorTree",  -- Include the BehaviorTree project modules
        "%{wks.location}/Core",           -- Include the Core project modules
        VCPKG_INCLUDE,                    -- Include vcpkg dependencies
    }

    links
    {
        "BehaviorTree",  -- Link with BehaviorTree library
        "Core",           -- Link with Core library
    }

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

        -- buildoptions { "/Z7" }

    filter "configurations:Release"
        defines "SANDBOX_RELEASE"
        runtime "Release"
        optimize "on"
