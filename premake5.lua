workspace "Pong"
    configurations { "Debug", "Release" }

    group "Depenencies"
        include "dependencies/Gemstone"
    group ""

    include "Pong"
