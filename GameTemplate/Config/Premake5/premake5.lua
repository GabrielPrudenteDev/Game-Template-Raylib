
os.chdir('../../')
WorkspaceName = path.getbasename(os.getcwd())
LocationPath = 'Intermediate/ProjectFiles'
ObjecstPath = 'Intermediate/Build'
TargetPath = 'Binaries/%{cfg.platform}/%{cfg.buildcfg}'
ContentPath = '' .. path.getabsolute('Content') .. '/'
PrjName = WorkspaceName

function LinkUtilities()
    includedirs {'Source/ThirdParty/Utilities'}


    files {'Source/ThirdParty/Utilities/**.h', 'Source/ThirdParty/Utilities/**.c', 'Source/ThirdParty/Utilities/**.hpp', 'Source/ThirdParty/Utilities/**.cpp'}

    vpaths {
        ['Source/ThirdParty/Utilities/Public'] = {'Source/ThirdParty/Utilities/**.h', 'Source/ThirdParty/Utilities/**.hpp' },
        ['Source/ThirdParty/Utilities/Private'] = { 'Source/ThirdParty/Utilities/**.c', 'Source/ThirdParty/Utilities/**.cpp'}
    }

end

function LinkRaylib()

    disablewarnings { "4996" }
    disablewarnings { "4244" }
    disablewarnings { "4305" }
    disablewarnings { "4305" }
    disablewarnings { "4018" }

    defines {'PLATFORM_DESKTOP'}

    includedirs {'Source/ThirdParty/Raylib'}
    includedirs {'Source/ThirdParty/Raylib/external'}
    includedirs {'Source/ThirdParty/Raylib/external/glfw/include'}

    files {'Source/ThirdParty/Raylib/*.h', 'Source/ThirdParty/Raylib/*.c'}

    vpaths {
        ['Source/ThirdParty/Raylib/Public'] = {'Source/ThirdParty/Raylib/*.h', },
        ['Source/ThirdParty/Raylib/Private'] = {'Source/ThirdParty/Raylib/*.c'}
    }

end

workspace(WorkspaceName)

    configurations {"Debug-Game" , "Release-Game", "Shipping"}
    platforms {"Win32", "Win64"}

project(PrjName).group = 'Games'

    language('C++')

    kind('ConsoleApp')

    targetdir(TargetPath)
    objdir(ObjecstPath)
    location(LocationPath)

    os.mkdir('Content')
    os.mkdir('Source/' .. PrjName)

-- MACROS
    defines {'GAME_NAME="' .. PrjName .. '"'}

    filter {'configurations:Debug-Game'}
        defines {'DEBUG_MODE'}
        defines {'CONTENTPATH="' .. ContentPath .. '"'}
        symbols 'On'

    filter {'configurations:Release-Game'}
        defines {'RELEASE_MODE'}
        defines {'CONTENTPATH="' .. ContentPath .. '"'}
        optimize 'On'

    filter {'configurations:Shipping'}
        defines {'SHIPPING_MODE'}
        defines {'CONTENTPATH="Content/"'}
        optimize 'On'
        symbols 'Off'
        kind "WindowedApp"
		entrypoint "mainCRTStartup"

        FilesFrom = path.getabsolute("Content")
        FileTo = path.getabsolute("Binaries/Shipping/%{cfg.platform}/Content/")
        targetdir("Binaries/Shipping/%{cfg.platform}")
        postbuildmessage "Copying Content Files..."
        -- copy a file from the objects directory to the target directory
        postbuildcommands { "{COPYDIR} %{FilesFrom} %{FileTo}" }

    filter {'platforms:Win32'}
        architecture('x86')
        system('Windows')

    filter {'platforms:Win64'}
        architecture('x86_64')
        system('Windows')

    filter "system:Unix"
        system "linux"
        defines {'PLATFORM_LINUX'}
        cppdialect "gnu++17"

    filter "system:Windows"
        system "windows"
        defines {'PLATFORM_WINDOWS'}
        links {'winmm', 'opengl32'}
        cppdialect "C++17"

    filter "system:Mac"
        system "macosx"
        defines {'PLATFORM_MAC'}

    filter {}

    includedirs {'Source/%{PrjName}'}

    files {'Config/AppIcon/ResourceGame.rc'}
    files {'Source/*.h', 'Source/*.hpp', 'Source/*.c', 'Source/*.cpp'}
    files {'Source/%{PrjName}/**.h', 'Source/%{PrjName}/**.hpp', 'Source/%{PrjName}/**.c', 'Source/%{PrjName}/**.cpp'}

    vpaths {
        ['Config/'] = {'Config/AppIcon/*.rc'},
        ['Source/'] = {'Source/*.h', 'Source/*.hpp', 'Source/*.c', 'Source/*.cpp'},
        ['Source/%{PrjName}/*'] = {'Source/%{PrjName}/**.h', 'Source/%{PrjName}/**.hpp', 'Source/%{PrjName}/**.c', 'Source/%{PrjName}/**.cpp'}
    }

    LinkRaylib()
    LinkUtilities()


    include "ProjectSettings.lua"

    newaction {
        trigger     = "GeneratorVs2017",
        description = "Install the software",
        execute     = function ()
            Filename = "../../Project.bat";
            Content = SettingsString
            Content = Content:gsub("PROJECTNAME", WorkspaceName)
            Content = Content:gsub("VSVERSION", "vs2017")
            Content = Content:gsub("VSPATH", Vs2017Path)
            io.writefile(Filename, Content)
        end
    }

    newaction {
        trigger     = "GeneratorVs2019",
        description = "Install the software",
        execute     = function ()
            Filename = "../../Project.bat";
            Content = SettingsString
            Content = Content:gsub("PROJECTNAME", WorkspaceName)
            Content = Content:gsub("VSVERSION", "vs2019")
            Content = Content:gsub("VSPATH", Vs2019Path)
            io.writefile(Filename, Content)
        end
    }

    newaction {
        trigger     = "GeneratorVs2022",
        description = "Install the software",
        execute     = function ()
            Filename = "../../Project.bat";
            Content = SettingsString
            Content = Content:gsub("PROJECTNAME", WorkspaceName)
            Content = Content:gsub("VSVERSION", "vs2022")
            Content = Content:gsub("VSPATH", Vs2022Path)
            io.writefile(Filename, Content)
        end
     }

