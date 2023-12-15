project "Pong"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    architecture "x86_64"

    flags "MultiProcessorCompile"

    targetdir "%{wks.location}/build/bin/%{cfg.name}/%{prj.name}"
	objdir "%{wks.location}/build/obj/%{cfg.name}/%{prj.name}"

    files { 
        "include/**.h", 
        "src/**.cpp" 
    }

    filter "configurations:Debug"
		defines { "PONG_DEBUG", "GEM_DEBUG" }
        runtime "Debug"
        symbols "On"
	filter "configurations:Release"
		defines { "PONG_RELEASE", "GEM_RELEASE" }
        runtime "Release"
        optimize "On"
	filter {}

    includedirs { 
        "../dependencies/Gemstone/include", 
        "../dependencies/Gemstone/dependencies/GLEW/include",
        "../dependencies/Gemstone/dependencies/GLFW/include",
        "../dependencies/Gemstone/dependencies/ImGui/include/ImGui",
        "../dependencies/Gemstone/dependencies/ImGui/include/ImPlot",
        "../dependencies/Gemstone/dependencies/stb_image",
        "include"
    }

    links {
        "Gemstone",
        "glew32s",
        "opengl32",
        "glfw3",
        "ImGui"
    }

    libdirs {
        "../dependencies/Gemstone/dependencies/GLFW/lib-vc2022",
        "../dependencies/Gemstone/dependencies/GLEW/lib/Release/x64",
        "../build/bin/debug/Gemstone"
    }
