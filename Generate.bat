@echo off
vcpkg install --triplet x64-windows-static
premake5.exe vs2022
pause