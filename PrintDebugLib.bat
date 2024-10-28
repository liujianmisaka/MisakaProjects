@echo off
setlocal enabledelayedexpansion

rem Set the directory path
set "dirPath=D:\dev\MisakaProjects\vcpkg_installed\x64-windows-static\debug\lib"

rem Loop through all files in the directory
for %%f in ("%dirPath%\*") do (
    if not "%%~xf"=="" (
        echo "%%~nf",
    )
)

endlocal
pause