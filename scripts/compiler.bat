@echo off
setlocal EnableDelayedExpansion

cls

set PROJECT_ROOT=%~dp0..\
set SRC_DIR="%PROJECT_ROOT%src"
set BIN_DIR="%PROJECT_ROOT%bin"

set SRCS=
for /R "%PROJECT_ROOT%src" %%f in (*.c) do (
  set SRCS=!SRCS! "%%f"
)

set TARGET="%PROJECT_ROOT%bin\game.exe"

set CFLAGS=-I"%PROJECT_ROOT%bin\allegro\include"
set LDFLAGS=-L"%PROJECT_ROOT%bin\allegro\lib" -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_dialog -lallegro_main

gcc !SRCS! -o %TARGET% %CFLAGS% %LDFLAGS%

if %errorlevel% neq 0 (
  echo Compilation failed!
  pause
  exit /b
)

echo Compilation successful!

for %%i in (%*) do (
  if "%%i"=="--run" (
    %TARGET%
  )
)

endlocal
