DEL /S *.sln
DEL /S *.vcxproj
DEL /S *.vcxproj.filters
DEL /S *.vcxproj.user
DEL /S *.dll
DEL /q .vs

CALL dependencies\premake\premake5.exe vs2022

pause