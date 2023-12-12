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

    includedirs { 
        "../dependencies/Gemstone/include", 
        "../dependencies/Gemstone/dependencies/GLEW/include",
        "../dependencies/Gemstone/dependencies/GLFW/include",
        "../dependencies/Gemstone/dependencies/ImGui/include/ImGui",
        "../dependencies/Gemstone/dependencies/ImGui/include/ImPlot",
        "../dependencies/Gemstone/dependencies/stb_image",
        "include"
    }

    links { "Gemstone" }
    links {
        "glew32s",
        "opengl32",
        "glfw3",
        "ImGui"
    }

    libdirs {
        "../dependencies/Gemstone/dependencies/GLFW/lib-vc2022",
        "../dependencies/Gemstone/dependencies/GLEW/lib/Release/x64"
    }

    postbuildcommands { "{COPYFILE} ..\\build\\bin\\Debug\\Gemstone\\Gemstone.dll ..\\build\\bin\\debug\\Pong" }
    -- copylocal { "Gemstone" }