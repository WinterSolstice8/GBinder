@echo off

REM ** Find where Visual Studio is installed..
set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%vswhere%" set "vswhere=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%vswhere%" (
	echo [ERROR] Failed to locate where Visual Studio is installed; cannot continue...
	exit 1
)

REM ** Find where the VC package is installed..
for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
  set vc_dir=%%i
)
if not exist "%vc_dir%\VC\Auxiliary\Build\vcvars32.bat" (
	echo [ERROR] Failed to locate where the required VC++ tools is installed; cannot continue...
	exit 1
)

REM ** Run the VC++ native command line tools script..
call "%vc_dir%\VC\Auxiliary\Build\vcvars32.bat"

REM ** Build...
msbuild GBinder.sln -t:Rebuild -p:Configuration=Debug

pause
