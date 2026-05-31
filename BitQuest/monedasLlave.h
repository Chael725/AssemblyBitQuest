#include <stdlib.h>
#include <time.h>
#include "juego.h"

void colocar_monedas(char mapa[FIL][COL + 1]) {
    srand(time(NULL));

    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            if (mapa[i][j] == '.') {
                if ((rand() % 100) < 3) {
                    mapa[i][j] = 'M';
                }
            }
        }
    }

    for (int i = 0; i < 10;) {
        int filaAleatoria = rand() % FIL;
        int colAleatoria = rand() % COL;

        if (mapa[filaAleatoria][colAleatoria] == '.') {
            mapa[filaAleatoria][colAleatoria] = 'M';
            i++;
        }
    }
}

void colocar_llave(char mapa[FIL][COL + 1]) {
    srand(time(NULL));


    for (int i = 0; i < 2;) {
        int filaAleatoria = rand() % FIL + 20;
        int colAleatoria = rand() % COL + 15;

        if (mapa[filaAleatoria][colAleatoria] == '.') {
            mapa[filaAleatoria][colAleatoria] = 'K';
            i++;
        }
    }
}