@echo off
setlocal EnableDelayedExpansion

set "debug_build=true"
set "optimize_build=false"
set "remove_dirs=false"
set "install_prefix=.."

:parse_loop
if "%~1"=="" goto :end_parse
if "%~1"=="-I" set "install_prefix=%~2" & shift & shift & goto parse_loop
if "%~1"=="--install_prefix" set "install_prefix=%~2" & shift & shift & goto parse_loop
if "%~1"=="-D" set "debug_build=true" & shift & goto parse_loop
if "%~1"=="--debug-build" set "debug_build=true" & shift & goto parse_loop
if "%~1"=="-d" set "debug_build=false" & shift & goto parse_loop
if "%~1"=="--no-debug-build" set "debug_build=false" & shift & goto parse_loop
if "%~1"=="-O" set "optimize_build=true" & shift & goto parse_loop
if "%~1"=="--optimize-build" set "optimize_build=true" & shift & goto parse_loop
if "%~1"=="-o" set "optimize_build=false" & shift & goto parse_loop
if "%~1"=="--no-optimize-build" set "optimize_build=false" & shift & goto parse_loop
if "%~1"=="-R" set "remove_dirs=true" & shift & goto parse_loop
if "%~1"=="--remove-build-dirs" set "remove_dirs=true" & shift & goto parse_loop
if "%~1"=="-h" goto :help
if "%~1"=="--help" goto :help
echo Invalid option: %1
goto :eof

:end_parse


if "%remove_dirs%"=="true" (
    echo Removing build directories...
    rmdir /s /q "./cmake-build-debug"
    rmdir /s /q "./cmake-build-release"
)
if "%debug_build%"=="true" (
    if not exist ".\cmake-build-debug" mkdir ".\cmake-build-debug"
    pushd ".\cmake-build-debug"
    echo Compiling in Debug mode...
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    if errorlevel 1 exit /b 1
    cmake --build .
    if errorlevel 1 exit /b 1
    cmake --install .
    popd
)

if "%optimize_build%"=="true" (
    if not exist ".\cmake-release-debug" mkdir ".\cmake-release-debug"
    pushd ".\cmake-release-debug"

    echo Compiling in Release mode...
    cmake -DCMAKE_BUILD_TYPE=Release ..
    if errorlevel 1 exit /b 1
    cmake --build .
    if errorlevel 1 exit /b 1
    cmake --install .
    popd
)

if "%remove_dirs%"=="true" (
    echo Removing build directories...
    rmdir /s /q "./cmake-build-debug"
    rmdir /s /q "./cmake-build-release"
)
endlocal

goto :eof

:help
echo Usage: compile.bat [options]
echo Options:
echo  -h      --help                  Show help message.
echo  -O      --optimize-build        Compile with optimization.
echo  -o      --no-optimize-build     Compile without optimization.
echo  -D      --debug-build           Compile with debug options.
echo  -d      --no-debug-build        Compile without debug options.
echo  -I      --install_prefix        Installation path.
echo  -R      --remove-build-dirs     Remove build dirs after install.
goto :eof


