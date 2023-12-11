project "Pong"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    flags "MultiProcessorCompile"

    files { 
        "src/**.h", 
        "src/**.cpp" 
    }

    includedirs { 
        "../dependencies/Gemstone/Gemstone/src", 
        "src" 
    }

    links { "Gemstone" }

    postbuildcommands { "{COPYFILE} ..\\dependencies\\Gemstone\\Gemstone\\build\\bin\\debug\\Gemstone.dll bin\\debug" }