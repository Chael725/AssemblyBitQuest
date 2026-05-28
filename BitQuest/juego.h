#ifndef JUEGO_H
#define JUEGO_H

#include <stdio.h>
#include <stdlib.h>

//Dimensiones del mapa
#define FILAS_MAPA 60
#define COLS_MAPA 60

//Dimensiones de la vista
#define FILAS_VISTA 20
#define COLS_VISTA 20

//Elementos del mapa
#define PARED '#'
#define CAMINO '.'
#define JUGADOR 'P'
#define MONEDA 'M'
#define LLAVE 'K'
#define PUERTA 'D'
#define SALIDA 'E'

//Estado del jugador
typedef struct {
    int fila;
    int columna;
    int monedas;
    int tiene_llave;
    int pasos;
} Jugador;




#endif