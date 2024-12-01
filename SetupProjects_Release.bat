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
setlocal enabledelayedexpansion

REM 配置 shaderc.exe 的路径
set SHADERC_PATH=.\Vendor\shaderc.exe

REM 检查 shaderc.exe 是否存在
if not exist "%SHADERC_PATH%" (
    echo [ERROR] shaderc.exe not found in the current directory!
    pause
    exit /b 1
)

REM 设置着色器的根目录
set SHADER_ROOT=.\Assets\Shaders\bgfx

REM 输出目录
set OUTPUT_DIR=.\Assets\Shaders\bgfx\compiled

REM varying.def.sc 文件路径
set VARYING_DEF=%SHADER_ROOT%\varying.def.sc

REM 创建输出目录（如果不存在）
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM 支持的平台列表（可根据需要修改）
set PLATFORM=windows

REM 设置 shader profile (例如：ps_5_0, spirv, 120, 130, 330)
set SHADER_PROFILE=150

REM 查找并编译所有 vs_*.sc 和 fs_*.sc 着色器
for /r "%SHADER_ROOT%" %%f in (vs_*.sc fs_*.sc) do (
    set SHADER_FILE=%%f
    set SHADER_NAME=%%~nf
    set SHADER_TYPE=

    REM 根据文件名决定着色器类型
    if "!SHADER_NAME:~0,3!"=="vs_" (
        set SHADER_TYPE=vertex
    ) else if "!SHADER_NAME:~0,3!"=="fs_" (
        set SHADER_TYPE=fragment
    ) else (
        echo [WARNING] Unrecognized shader type: %%f
        continue
    )

    REM 输出文件名（保持文件结构）
    set OUTPUT_FILE=%OUTPUT_DIR%\!SHADER_NAME!.bin

    REM 编译着色器
    echo [INFO] Compiling: !SHADER_FILE! as !SHADER_TYPE!
    "%SHADERC_PATH%" -f "!SHADER_FILE!" -o "!OUTPUT_FILE!" --platform %PLATFORM% --type !SHADER_TYPE! --profile !SHADER_PROFILE! --varyingdef %VARYING_DEF%

    if errorlevel 1 (
        echo [ERROR] Failed to compile: !SHADER_FILE!
        pause
        exit /b 1
    )
)

endlocal
echo [INFO] bgfx Shader 编译完成.

REM 安装依赖库
vcpkg install --triplet x64-windows-static
echo [INFO] 依赖库安装完成.

REM 生成项目文件
.\Vendor\premake5.exe vs2022
echo [INFO] 项目文件已生成.

REM 编译项目
msbuild MisakaProjects.sln /p:Configuration=%CONFIGURATION%

REM 复制文件到输出目录
xcopy /Y /E /I "Assets" "%OUTPUT_DIR%\Assets"
xcopy /Y /E /I "bin\%CONFIGURATION%-windows-x86_64\Core\Core.lib" "%OUTPUT_DIR%\Core.lib"
xcopy /Y /E /I "bin\%CONFIGURATION%-windows-x86_64\Sandbox\Sandbox.exe" "%OUTPUT_DIR%\Sandbox.exe"

echo [INFO] 项目编译完成，文件已复制到 %OUTPUT_DIR%
pause