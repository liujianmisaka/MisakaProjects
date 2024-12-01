@echo off

REM 设置终端编码为 UTF-8
chcp 65001

vcpkg install --triplet x64-windows-static
echo [INFO] 依赖库安装完成.
pause
