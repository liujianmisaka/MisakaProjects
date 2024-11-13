@echo off
vcpkg install --triplet x64-windows-static
.\Vendor\premake5.exe vs2022
pause