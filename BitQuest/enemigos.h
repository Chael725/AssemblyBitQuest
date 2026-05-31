#include <stdlib.h>
#include <time.h>
#include "juego.h"

void colocar_enemigos(char mapa[FIL][COL + 1]) {
    for (int i = 0; i < 5;) {
        int filaAleatoria = rand() % FIL;
        int colAleatoria = rand() % COL;

        if (mapa[filaAleatoria][colAleatoria] == '.') {
            mapa[filaAleatoria][colAleatoria] = '&';
            i++; 
        }
    }
}