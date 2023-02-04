# Game-Template-Raylib
 Template to generate Visual Studio 2017, 2019 and 2022 project using Raylib.

# Instructions  
Copy and rename the Game Template folder so your project has the same name.  

Generate new Project = Go to the Config/Generator folder and choose the Visual Studio version  
  
Add new source files = After creating the class, it is necessary to update the project by opening the "Project.bat" file.  
  
To change the executable icon = Change the App Icon.ico file in the path "Config/App Icon"  

# Commands to build  
To use paseos command as argument for file "Project" Ex "./Project make"  
Make  = Debug Win32  
run  = Debug Win32  
make-b-w32 = Debug Win32  
make-r-w32 = Release Win32  
make-s-w32 = Shipping Win32  
make-b-w64 = Debug Win64  
make-r-w64 = Release Win64  
make-s-w64 = Shipping Win64  

# Macros
DEBUG_MODE   
RELEASE_MODE  
SHIPPING_MODE  
GAMENAME  
CONTENTPATH  Full path of the "Content" folder.  

# Note
In Shipping mode, all contents of the "Content" folder will be copied to a Shipping folder next to the executable for easy distribution.  
The "CoreMinimal.h" file contains some additional inclusions like an Asset Search Macro that changes automatically depending on the build mode. 
To use Visual Studio Code it is necessary to have some version of Visual Stuido installed or Build Tools for Visual Studio.   
All assets have to be in the "Content" folder so they can be copied and located regardless of build mode.  
The file "FileSystem.h" is a system log that contains Macros "GT_ASSERT" to check for possible errors on null pointers, GT_FASTLOG generates a quick visual only log message with warning color. GT_LOG to generate more advanced logs capable of showing on the screen with different colors and being able to save the log in a file.  
  
# Credits
Raylib -> https://www.raylib.com/  
Canal do Oliveira Dev -> https://www.youtube.com/channel/UC-S8m-8Lred5NLJKhzIHOSg  
  
Texts translated from Google Translate.

