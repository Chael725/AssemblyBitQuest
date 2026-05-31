#include <stdlib.h>
#include <time.h>
#include "juego.h"

void colocar_enemigos(char mapa[FIL][COL + 1]) {
    for (int i = 0; i < 5;) {
        int filaAleatoria = rand() % FIL + 5;
        int colAleatoria = rand() % COL + 5;

        if (mapa[filaAleatoria][colAleatoria] == '.') {
            mapa[filaAleatoria][colAleatoria] = '&';
            i++; 
        }
    }
}

void mover_enemigos(char mapa[FIL][COL + 1], int *playing, int jugadorFila, int jugadorColumna) {
    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            if (mapa[i][j] == '&') {
                // 0=Arriba, 1=Abajo, 2=Izquierda, 3=Derecha.
                int direccion = rand() % 4;
                int nF = i;
                int nC = j;

                if (direccion == 0) nF--;
                else if (direccion == 1) nF++;
                else if (direccion == 2) nC--;
                else if (direccion == 3) nC++;

            }
        }
    }

}