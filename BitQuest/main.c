#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <ctype.h>
#include "mapas.h"

int main() {
    system("chcp 437 > nul");
    system("cls");

    //Posicion donde comenzara el jugador
    int jugadorFila = 1;
    int jugadorColumna = 1;

    char input;
    int playing = 1;

    //Ciclo principal
    while (playing){
        //Dibujar la vista de 20x20 del laberinto
        imprimir_ventana(mapa1, jugadorFila, jugadorColumna);
    
        input = toupper(_getch());

        int nuevaFila = jugadorFila;
        int nuevaColumna = jugadorColumna;

        if (input == 'W') nuevaFila--;
        else if (input == 'S') nuevaFila++;
        else if (input == 'A') nuevaColumna--;
        else if (input == 'D') nuevaColumna++;
        else if (input == 'Q') playing = 0;

        //Validar la colision con las paredes
        if (playing && mapa1[nuevaFila][nuevaColumna] != '#'){

            mapa1[jugadorFila][jugadorColumna] = '.';
            
            //Actualizar las coordenadas del jugador
            jugadorFila = nuevaFila;
            jugadorColumna = nuevaColumna;
            
            //Dibujar el jugador en la nueva posición
            mapa1[jugadorFila][jugadorColumna] = 'P';
        }
    }

    system("cls");

    return 0;
}