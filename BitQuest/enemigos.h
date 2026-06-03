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

                // Se que todavía no comento todo, pero esta parte es importante y el porque del cambio.
                if (mapa[nF][nC] == '.') {
                    mapa[i][j] = '.';   
                    mapa[nF][nC] = 'F'; // Podras ver que aquí he puesto una F, que realmente puede ser cualquier caracter que no se use en el juego.
                    // Yo note que los enemigos se movian raro, aveces doble, entonces investigando un poco...
                    // Se puede notar que pues se sigue recorriendo la matrizpara buscar a los demas enemigos.
                    // Entonces, si el & se movio a la derecha o abajo, al seguir escaneando la matriz,
                    // Se va volver a topar con el & y por eso se vuelve a mover, con muchamala suerte, estopuede pasar infinitamente,
                    // Por eso se pone la F, para que cuando siga escaneando, no mueva 2 vecesel mismo enemigo.
                                        
                }
            }
        }
    }

    // Pero, no lo podemos dejar como F, así que después de mover a todos los enemigos, volvemos a escanear la matriz para cambiar las F por &.
    // Es muy poco eficiente, pero no tengo el conocimiento de como optimizar esto.
    // A este punto cada función escanea la matriz...
    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            if (mapa[i][j] == 'F') {
                mapa[i][j] = '&';
            }
        }
    }
}