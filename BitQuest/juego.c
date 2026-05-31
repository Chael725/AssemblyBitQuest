#include <stdio.h>
#include "juego.h"

void imprimir_ventana(char mapa[FIL][COL +1], int jugadorFila, int jugadorColumna){
    //Calcular el inicio de la vista para centrar al jugador
    int filInicio = jugadorFila - (VIEW / 2);
    int colInicio = jugadorColumna - (VIEW / 2);

    //Evitar salir por arriba o por la izquierda
    if (filInicio < 0){
        filInicio = 0;
    }
    if (colInicio < 0){
        colInicio = 0;
    }
    // Evitar salir por abajo o por la derecha
    if (filInicio > FIL - VIEW){
        filInicio = FIL - VIEW;
    }
    if (colInicio > COL - VIEW){
        colInicio = COL - VIEW;
    }


    //Imprimir la ventana 20x20
    for (int i = 0; i < VIEW; i++) {
        for (int j = 0; j < VIEW; j++) {
            printf("%c", mapa[filInicio + i][colInicio + j]);
        }
        printf("\n");
    }
}