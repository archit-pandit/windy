REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all .c files ----------------------------
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

REM set args for clang ------------------------------------
SET assembly=engine

REM -g: export debug info
REM -shared: create .dll
SET compilerFlags=-g -shared -Wvarargs -Wall -Werror

REM -Isrc: include src dir
REM -I%...% include vulkan dir
SET includeFlags=-Isrc -I%VULKAN_SDK%/includeFlags

REM -luser32: link with user32
REM -lvulkan-1: link with vulkan-1
REM -L%...%: include vulkan lib
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib

SET defines=-D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%%..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%