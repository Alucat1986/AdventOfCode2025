@echo off
if /I "%1"=="" (
    echo No arguments provided, using default: nobuild_sfml static
    set SFMLBUILD=nobuild_sfml
    set BUILDTYPE=static
) else (
    if /I "%1"=="static" (
        echo BUILDTYPE set to static, SFMLBUILD to default: nobuild_sfml
        set SFMLBUILD=nobuild_sfml
        set BUILDTYPE=static
    ) else (
        set SFMLBUILD=%1
        if /I "%2"=="" (
            echo SFMLBUILD provided, but BUILDTYPE opting to default: static
            set BUILDTYPE=static
        ) else (
            BUILDTYPE=%2
        )
    )
)

echo Building with %SFMLBUILD% and %BUILDTYPE%...

if /I "%SFMLBUILD%"=="build_sfml" (
REM Step 1: Build SFML with CMake
cd Vendor\SFML
if not exist build mkdir build
if /I "%BUILDTYPE%"=="static" (
    echo Building SFML as static libraries...
    cmake -DBUILD_SHARED_LIBS=OFF -B build
    cmake --build build --config Release
    cmake --build build --config Debug
) else (
    echo Building SFML as dynamic libraries...
    cmake -DBUILD_SHARED_LIBS=ON -B build
    cmake --build build --config Release
    cmake --build build --config Debug
)
cd ..\..
)

REM Step 2: Run Premake
if /I "%BUILDTYPE%"=="static" (
    echo Generating project files for static SFML...
    premake5 vs2022 --static-sfml=ON
) else (
    echo Generating project files for dynamic SFML...
    premake5 vs2022 --static-sfml=OFF
)

REM Step 3: Create output folders
echo Creating output directories...
if /I "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
    set arch="x86_64"
) else (
    set arch=%PROCESSOR_ARCHITECTURE%
)
set OutputDir=Release
mkdir Binaries\windows-%arch%\%OutputDir%\MicroTowerDefense
set OutputDir=Debug
mkdir Binaries\windows-%arch%\%OutputDir%\MicroTowerDefense

if /I "%BUILDTYPE%"=="static" (
    REM Step 4: No need for copying DLLs for static build
    echo No need for copying DLLs for static build.
) else (
    REM Step 4: Copy SFML DLLs (Release and Debug)
    echo Copying SFML DLLs to output directories...
    xcopy /Y /D Vendor\SFML\build\bin\Release\*.dll Binaries\windows-%arch%\Release\MicroTowerDefense\
    xcopy /Y /D Vendor\SFML\build\bin\Debug\*.dll Binaries\windows-%arch%\Debug\MicroTowerDefense\
)
echo Build script completed.
pause