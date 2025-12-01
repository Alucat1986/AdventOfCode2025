-- premake5.lua
include "preOptions.lua"

workspace "AdventOfCode2025"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Challenges"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/w44365", "/external:anglebrackets" }


	warnings "Extra"
	fatalwarnings { "All" }

	OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

	-- group "Core"
	--  include "MuffinEngine/premake5.lua"
	-- group ""
	
	include "Challenges/premake5.lua"