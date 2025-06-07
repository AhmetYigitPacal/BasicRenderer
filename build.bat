@echo off
setlocal

set BUILD_TYPE=Release
set EXEC_NAME=BasicRenderer

if not exist build (
    echo Building program...
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -G "Ninja"
)

cmake --build build --clean-first

endlocal
