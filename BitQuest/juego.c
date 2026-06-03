#include <stdio.h>
#include "juego.h"
#include "ventana.h"

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
        gotoxy(3, 3 + i);
        for (int j = 0; j < VIEW; j++) {
            if (mapa[filInicio + i][colInicio + j] == '.') {
                setColor(2);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if (mapa[filInicio + i][colInicio + j] == '#') {
                setColor(8);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if (mapa[filInicio + i][colInicio + j] == 'P') {
                setColor(11);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if (mapa[filInicio + i][colInicio + j] == 'M') {
                setColor(14);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if (mapa[filInicio + i][colInicio + j] == 'K') {
                setColor(6);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if (mapa[filInicio + i][colInicio + j] == '&') {
                setColor(4);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if(mapa[filInicio + i][colInicio + j] == 'D' ) {
                setColor(13);
                printf("%c", mapa[filInicio + i][colInicio + j]);

            }else if(mapa[filInicio + i][colInicio + j] == '-' || mapa[filInicio + i][colInicio + j] == '|') {
                setColor(12);
                printf("%c", mapa[filInicio + i][colInicio + j]);

            }else if(mapa[filInicio + i][colInicio + j] == 'I' || mapa[filInicio + i][colInicio + j] == 'O' ) {
                setColor(6);
                printf("O", mapa[filInicio + i][colInicio + j]);

            }else if(mapa[filInicio + i][colInicio + j] == '*' ) {
                setColor(4);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if(mapa[filInicio + i][colInicio + j] == '+' ) {
                setColor(4);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else if(mapa[filInicio + i][colInicio + j] == 'E') {
                setColor(2);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }else {
                setColor(7);
                printf("%c", mapa[filInicio + i][colInicio + j]);
            }
        }
        fflush(stdout);
    }
}