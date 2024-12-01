@echo off

REM 设置终端编码为 UTF-8
chcp 65001

REM 生成项目文件
.\Vendor\premake5.exe vs2022
echo [INFO] 项目文件已生成.
pause
