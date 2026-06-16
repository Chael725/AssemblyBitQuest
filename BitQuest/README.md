----- Proyecto Final Ensamblador: BitQuest -----

Este repositorio contiene el código fuente de BitQuest, un videojuego de consola desarrollado mediante programación híbrida en C y Lenguaje Ensamblador (NASM de 64 bits) para Windows.

Requisitos Previos:
Para compilar y ejecutar este proyecto correctamente, tu entorno debe contar con:
* Sistema Operativo: Windows (64 bits).
* Compilador de C: GCC (MinGW-w64) configurado en las variables de entorno (PATH).
* Ensamblador: NASM configurado en las variables de entorno (PATH).

Instrucciones de Compilación Automática:
El proyecto incluye un script automatizado para facilitar la compilación. Solo sigue estos pasos:

1. Abre una terminal (Símbolo del sistema o PowerShell) en la carpeta raíz del proyecto.
2. Ejecuta el archivo por lotes escribiendo:
   `build.bat`
3. El script se encargará de ensamblar `rutinas.asm` a un archivo `.obj` y compilar los archivos `.c` generando el ejecutable final `BitQuest.exe`.

Instrucciones de Ejecución:
Una vez compilado el proyecto sin errores, puedes iniciar el juego desde la misma terminal ejecutando:
`BitQuest.exe`
