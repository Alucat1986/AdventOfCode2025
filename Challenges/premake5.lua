project "Challenges"
    language "C++"
    cppdialect "C++23"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files {
        "Source/**.hpp",
        "Source/**.cpp",
        "Data/**.txt",
        "**.lua",
        "**.md"
    }

    vpaths {
        ["Build"] = "**.lua",
        ["Data/*"] = "Data/**.txt",
		["Docs"] = "**.md",
        --["Header/*"] = "Source/**.hpp",
        ["Source/*"] = { "Source/**.cpp", "Source/**.hpp" }
	}

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    if _OPTIONS["static-sfml"] == "ON" then
        defines { "SFML_STATIC" }
        LinkAffix = "-s"
    else
        LinkAffix = ""
    end
    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        kind "ConsoleApp"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        kind "ConsoleApp"
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        kind "WindowedApp"
        runtime "Release"
        optimize "On"
        symbols "Off"
