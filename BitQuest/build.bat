@echo off
echo =========================================
echo Compilando BitQuest...
echo =========================================

echo 1. Ensamblando rutinas.asm...
nasm -f win64 rutinas.asm -o rutinas.obj
if %errorlevel% neq 0 (
    echo [ERROR] Fallo al compilar Ensamblador.
    pause
    exit /b %errorlevel%
)

echo 2. Compilando y enlazando C...
gcc main.c juego.c rutinas.obj -o BitQuest.exe
if %errorlevel% neq 0 (
    echo [ERROR] Fallo al compilar GCC.
    pause
    exit /b %errorlevel%
)

echo =========================================
echo Compilacion exitosa. Ejecutando juego...
echo =========================================
echo.

BitQuest.exe
pause