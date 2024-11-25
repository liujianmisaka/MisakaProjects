@echo off
setlocal

REM 设置终端编码为 UTF-8
chcp 65001

REM 设置变量
set CONFIGURATION=Release
set OUTPUT_DIR=%~dp0Release

REM 加载 Visual Studio 开发环境
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

REM 创建输出目录
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM 编译着色器(使用CompileShader.bat)
call Scripts/CompileShader.bat

REM 安装依赖库
call Scripts/InstallPackages.bat

REM 生成项目文件
call Scripts/GenerateProjectOnly.bat

REM 编译项目
msbuild MisakaProjects.sln /p:Configuration=%CONFIGURATION%

REM 复制文件到输出目录
xcopy /Y /E /I "Assets" "%OUTPUT_DIR%\Assets"
xcopy /Y /E /I "bin\%CONFIGURATION%-windows-x86_64\Core\Core.lib" "%OUTPUT_DIR%\Core.lib"
xcopy /Y /E /I "bin\%CONFIGURATION%-windows-x86_64\Sandbox\Sandbox.exe" "%OUTPUT_DIR%\Sandbox.exe"

echo [INFO] 项目编译完成，文件已复制到 %OUTPUT_DIR%
pause