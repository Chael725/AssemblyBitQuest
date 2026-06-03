#include "drakeAnim.h"
#include <time.h>
#include <conio.h>

void menu(char input) {
    clock_t drakeTime = clock();
    gotoxy(137, 10);
    setColor(12);
    printf("BitQuest");
    gotoxy(137, 11);
    printf("Leyends");
    setColor(7);
    gotoxy(136, 15);
    printf("Bienvenido a");
    gotoxy(134, 16);
    printf("nuestro laberinto");
    gotoxy(134, 18);
    printf("Si eres valiente...");
    gotoxy(134, 19);
    printf("Presiona 'Q'");

    while (input != 'Q') {
        clock_t currentTime = clock();
        if ((currentTime - drakeTime) >= 1000) { 
            drakeArmar();
            drakeTime = currentTime;
        }

        if (_kbhit()) {
            input = toupper(_getch());
        }

    }
}
