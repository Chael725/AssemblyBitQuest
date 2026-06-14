#ifndef CANONES_H
#define CANONES_H

#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "juego.h"


void generar_proyectiles(char mapa[FIL][COL + 1], int *playing) {
    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            if (mapa[i][j] == '=') {
                
                if (j + 1 < COL) {
                    if (mapa[i][j + 1] == '\'' || mapa[i][j + 1] == '.') {
                        mapa[i][j + 1] = 'O'; 
                    }else if (mapa[i][j + 1] == 'P') {
                        *playing = 0; return; 
                    }
                }

                if (j - 1 >= 0) {
                    if (mapa[i][j - 1] == '\'' || mapa[i][j - 1] == '.') {
                        mapa[i][j - 1] = 'I';
                    } else if (mapa[i][j - 1] == 'P') {
                        *playing = 0; return;
                    }
                }
                
            }
        }
    }
}

void mover_proyectiles(char mapa[FIL][COL + 1], int *playing, int jugadorFila, int jugadorColumna) {
    
    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {

            // Movimiento a la drecha.
            if (mapa[i][j] == 'O') {
                int sigF = i;
                int sigC = j + 1;

                if (mapa[sigF][sigC] == 'P' || (sigF == jugadorFila && sigC == jugadorColumna)) {
                    mapa[i][j] = '.'; *playing = 0; return;
                }

                
                if (mapa[sigF][sigC] == '\'' || mapa[sigF][sigC] == '.') {
                    mapa[sigF][sigC] = 'X'; 
                    mapa[i][j] = '.'; 
                } else if (mapa[sigF][sigC] == '&' || mapa[sigF][sigC] == '#' || mapa[sigF][sigC] == '='){
                    mapa[i][j] = 'v';
                }
            }
            // Movimiento a la izquierda.
            else if (mapa[i][j] == 'I') {
                int sigF = i;
                int sigC = j - 1;

                if (mapa[sigF][sigC] == 'P' || (sigF == jugadorFila && sigC == jugadorColumna)) {
                    mapa[i][j] = '.'; *playing = 0; return;
                }

                if (mapa[sigF][sigC] == '\'' || mapa[sigF][sigC] == '.') {
                    mapa[sigF][sigC] = 'Z'; 
                    mapa[i][j] = '.';
                } else if (mapa[sigF][sigC] == '&' || mapa[sigF][sigC] == '#' || mapa[sigF][sigC] == '=') {
                    mapa[i][j] = 'v';
                }
            }

        }
    }

    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            if (mapa[i][j] == 'X') mapa[i][j] = 'O';
            if (mapa[i][j] == 'Z') mapa[i][j] = 'I';

            if (mapa[i][j] == '+') {
                mapa[i][j] = '.';
            }
            if (mapa[i][j] == '*') {
                mapa[i][j] = '+'; 
            }
            if (mapa[i][j] == 'v') {
                mapa[i][j] = '*'; 
            }
            
        }
    }

    
}

#endif