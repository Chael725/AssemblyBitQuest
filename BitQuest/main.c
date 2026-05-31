#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> 
#include <ctype.h>
#include "mapas.h"
#include "ventana.h"
#include "monedasLlave.h"
#include "enemigos.h"


int main() {
    bool llave = false;
    colocar_monedas(mapa1);
    colocar_llave(mapa1);
    colocar_enemigos(mapa1);
    ocultarCursor();
    system("chcp 437 > nul");

    //Posicion donde comenzara el jugador
    int jugadorFila = 1;
    int jugadorColumna = 1;

    char input;
    int playing = 1;

    char mira = 'D';

    system("cls");

    //Ciclo principal
    while (playing){
        marco();
        reset();
        //Dibujar la vista de 20x20 del laberinto
        imprimir_ventana(mapa1, jugadorFila, jugadorColumna);
    
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


        //Validar la colision con las paredes
        if (llave && playing && mapa1[nuevaFila][nuevaColumna] == 'D'){
            mapa1[jugadorFila][jugadorColumna] = '.';
        
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;
            
            mapa1[jugadorFila][jugadorColumna] = 'P';
            playing = 0;
        }else if (playing && mapa1[nuevaFila][nuevaColumna] == 'K'){
            llave = true;
            mapa1[jugadorFila][jugadorColumna] = '.';
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;
            mapa1[jugadorFila][jugadorColumna] = 'P';
            
        }else if (playing && mapa1[nuevaFila][nuevaColumna] == '&'){
            mapa1[jugadorFila][jugadorColumna] = '.';
        
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;
            
            mapa1[jugadorFila][jugadorColumna] = 'P';
            playing = 0;
        }else if (playing && mapa1[nuevaFila][nuevaColumna] != '#' && mapa1[nuevaFila][nuevaColumna] != 'D') {

            mapa1[jugadorFila][jugadorColumna] = '.';
            
            //Actualizar las coordenadas del jugador
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;
            
            //Dibujar el jugador en la nueva posición
            mapa1[jugadorFila][jugadorColumna] = 'P';
        }

        if (playing) {
            mover_enemigos(mapa1, &playing, jugadorFila, jugadorColumna);
        }
    }

    system("cls");

    return 0;
}

