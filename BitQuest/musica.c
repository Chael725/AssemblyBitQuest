#include "musica.h"
#include <windows.h>
#include <stdio.h>

// Para la musica de fondo.
#include <mmsystem.h>

// Esto le dice al compilador que use la libreria de multimedia de Windows.
#pragma comment(lib, "winmm.lib")

void reproducir_musica(int opcion) { 
    
    if (opcion == 1) {
        mciSendString("open \"CancionFondo.mp3\" type mpegvideo alias fondo", NULL, 0, NULL);
    } else {
        mciSendString("open \"Mossbyte Maze.mp3\" type mpegvideo alias fondo", NULL, 0, NULL);
    }
    
    mciSendString("play fondo from 0 repeat", NULL, 0, NULL);
}

void detener_musica() {
    mciSendString("stop fondo", NULL, 0, NULL);
    mciSendString("close fondo", NULL, 0, NULL);
}

void mutear_musica() {
    mciSendString("setaudio fondo volume to 0", NULL, 0, NULL);
}

void desmutear_musica(int volumenRestaurar) {
    char comando[64];
    sprintf(comando, "setaudio fondo volume to %d", volumenRestaurar);
    mciSendString(comando, NULL, 0, NULL);
}

void cambiar_volumen(int nivel) {
    char comando[64];
    sprintf(comando, "setaudio fondo volume to %d", nivel);
    mciSendString(comando, NULL, 0, NULL);
}