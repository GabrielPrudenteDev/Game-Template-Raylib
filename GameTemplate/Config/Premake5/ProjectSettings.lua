Vs2017Path = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\Common7\\Tools\\VsDevCmd"
Vs2019Path = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\Common7\\Tools\\VsDevCmd"
Vs2022Path = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd"

SettingsString = [[@echo off
If "%~1" == "run" GOTO RunDebugWin64
IF "%~1" == "make" GOTO MakeDebugWin64
IF "%~1" == "make-d-w32" GOTO MakeDebugWin32
IF "%~1" == "make-d-w64" GOTO MakeDebugWin64
IF "%~1" == "make-r-w32" GOTO MakeReleaseWin32
IF "%~1" == "make-r-w64" GOTO MakeReleaseWin64
IF "%~1" == "make-s-w32" GOTO MakeShippingWin32
IF "%~1" == "make-s-w64" GOTO MakeShippingWin64

:Refress
echo "Project Refresh"

cd "./Config/Premake5"
call premake5.exe VSVERSION
cd "../../"
GOTO Done

:RunDebugWin64
echo "Run Debug Win64"
call "Binaries/Win64/Debug-Game/PROJECTNAME.exe"
GOTO Done

:MakeDebugWin32
echo "Make Project Debug Win32"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Debug-Game /p:Platform=Win32 %solutionFile%
GOTO Done

:MakeDebugWin64
echo "Make Project Debug Win64"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Debug-Game /p:Platform=Win64 %solutionFile%
GOTO Done

:MakeReleaseWin32
echo "Make Project Release Win32"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Release-Game /p:Platform=Win32 %solutionFile%
GOTO Done

:MakeReleaseWin64
echo "Make Project Release Win64"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Release-Game /p:Platform=Win64 %solutionFile%
GOTO Done

:MakeShippingWin32
echo "Make Project Shipping Win32"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Shipping /p:Platform=Win32 %solutionFile%
GOTO Done

:MakeShippingWin64
echo "Make Project Shipping Win64"
if not defined DevEnvDir (
    call "VSPATH"
)
set solutionFile = "Workspace.sln"
msbuild /t:Build /p:Configuration=Shipping /p:Platform=Win64 %solutionFile%
GOTO Done

:Done]]