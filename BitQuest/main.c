#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> 
#include <ctype.h>
#include <time.h>
#include "mapas.h"
#include "monedasLlave.h"
#include "enemigos.h"
#include "canones.h"
#include "menu.h"
extern void contar_entidades(char* mapa, int* c_enemigos, int* c_llaves, int* c_monedas);

int main() {

    system("mode con: cols=140 lines=55");
    
    bool llave = false;
    colocar_monedas(mapa1);
    colocar_enemigos(mapa1);
    colocar_llave(mapa1);
    ocultarCursor();

    int totalEnemigos = 0;
    int totalLlaves = 0;
    int totalMonedas = 0;

    contar_entidades((char*)mapa1, &totalEnemigos, &totalLlaves, &totalMonedas);

    printf("Enemigos en el mapa: %d\n", totalEnemigos);
    printf("Llaves en el mapa: %d\n", totalLlaves);
    printf("Monedas en el mapa: %d\n", totalMonedas);

    system("chcp 437 > nul");

    // Posicion donde comenzara el jugador
    int jugadorFila = 1;
    int jugadorColumna = 1;

    char input;
    int playing = 1;

    char mira = 'D';

    system("cls");

    menu(input);

    system("cls");
    
    clock_t disparo= clock();
    clock_t movBala= clock();

    marco(); 

    while (playing) {
        clock_t tiempoActual = clock();

        if ((tiempoActual - movBala) >= 300) { 
            mover_proyectiles(mapa1, &playing, jugadorFila, jugadorColumna);
            movBala = tiempoActual;
            
            reset();
            imprimir_ventana(mapa1, jugadorFila, jugadorColumna);
        }

        if ((tiempoActual - disparo) >= 2000) {
            generar_proyectiles(mapa1, &playing); 
            disparo = tiempoActual;
        }
    
        if (_kbhit()) { 
            input = toupper(_getch()); 

            int nuevaFila = jugadorFila;
            int nuevaColumna = jugadorColumna;

            if (input == 'W') { 
                nuevaFila--; 
                mira = 'W'; 
            }
            else if (input == 'S') { 
                nuevaFila++; 
                mira = 'S'; 
            }
            else if (input == 'A') { 
                nuevaColumna--; 
                mira = 'A'; 
            }
            else if (input == 'D') { 
                nuevaColumna++; 
                mira = 'D'; 
            }
            else if (input == 'Q') playing = 0;

            else if (input == 'E') {
                if (mira == 'W') {
                    if (mapa1[jugadorFila - 1][jugadorColumna] == '&') mapa1[jugadorFila - 1][jugadorColumna] = '.';
                    if (mapa1[jugadorFila - 1][jugadorColumna] == '.') mapa1[jugadorFila - 1][jugadorColumna] = '|';
                }
               
                else if (mira == 'S') {
                    if (mapa1[jugadorFila + 1][jugadorColumna] == '&') mapa1[jugadorFila + 1][jugadorColumna] = '.';
                    if (mapa1[jugadorFila + 1][jugadorColumna] == '.') mapa1[jugadorFila + 1][jugadorColumna] = '|';
                }
               
                else if (mira == 'A') {
                    if (mapa1[jugadorFila][jugadorColumna - 1] == '&') mapa1[jugadorFila][jugadorColumna - 1] = '.';
                    if (mapa1[jugadorFila][jugadorColumna - 1] == '.') mapa1[jugadorFila][jugadorColumna - 1] = '-';
                }
                
                else if (mira == 'D') {
                    if (mapa1[jugadorFila][jugadorColumna + 1] == '&') mapa1[jugadorFila][jugadorColumna + 1] = '.';
                    if (mapa1[jugadorFila][jugadorColumna + 1] == '.') mapa1[jugadorFila][jugadorColumna + 1] = '-';
                }
                
                // Limpiar el efecto de ataque.
                reset();
                imprimir_ventana(mapa1, jugadorFila, jugadorColumna);
                Sleep(200); 
                if (mapa1[jugadorFila - 1][jugadorColumna] == '|') mapa1[jugadorFila - 1][jugadorColumna] = '.';
                if (mapa1[jugadorFila + 1][jugadorColumna] == '|') mapa1[jugadorFila + 1][jugadorColumna] = '.';
                if (mapa1[jugadorFila][jugadorColumna - 1] == '-') mapa1[jugadorFila][jugadorColumna - 1] = '.';
                if (mapa1[jugadorFila][jugadorColumna + 1] == '-') mapa1[jugadorFila][jugadorColumna + 1] = '.';
            }

            // Validar la colision con las paredes y objetos
            if (llave && playing && mapa1[nuevaFila][nuevaColumna] == 'D'){
                mapa1[jugadorFila][jugadorColumna] = '.';
                jugadorFila = nuevaFila;
                jugadorColumna = nuevaColumna;
                mapa1[jugadorFila][jugadorColumna] = 'P';
            } else if (playing && mapa1[nuevaFila][nuevaColumna] == 'K') {
                llave = true;
                mapa1[jugadorFila][jugadorColumna] = '.';
                jugadorFila = nuevaFila;
                jugadorColumna = nuevaColumna;
                mapa1[jugadorFila][jugadorColumna] = 'P';
                
            }else if (playing && (mapa1[nuevaFila][nuevaColumna] == 'O' || mapa1[nuevaFila][nuevaColumna] == 'I')) {
                mapa1[jugadorFila][jugadorColumna] = '.';
                jugadorFila = nuevaFila;
                jugadorColumna = nuevaColumna;
                mapa1[jugadorFila][jugadorColumna] = 'P';
                playing = 0;
                
            } else if (playing && mapa1[nuevaFila][nuevaColumna] == '&') {
                mapa1[jugadorFila][jugadorColumna] = '.';
                jugadorFila = nuevaFila;
                jugadorColumna = nuevaColumna;
                mapa1[jugadorFila][jugadorColumna] = 'P';
                playing = 0;
            } else if (playing && mapa1[nuevaFila][nuevaColumna] != '#' && mapa1[nuevaFila][nuevaColumna] != 'D' && mapa1[nuevaFila][nuevaColumna] != '=') {
                mapa1[jugadorFila][jugadorColumna] = '.';
                jugadorFila = nuevaFila;
                jugadorColumna = nuevaColumna;
                mapa1[jugadorFila][jugadorColumna] = 'P';
            }

            if (playing) {
                mover_enemigos(mapa1, &playing, jugadorFila, jugadorColumna);
            }

            // Redibujamos después del movimiento del jugador
            reset();
            imprimir_ventana(mapa1, jugadorFila, jugadorColumna);
        }
    }

    system("cls");
    return 0;
}