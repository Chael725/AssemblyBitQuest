#include <windows.h>

void ocultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO aparCursor;
    aparCursor.dwSize = 10; 
    aparCursor.bVisible = FALSE; 
    SetConsoleCursorInfo(hCon, &aparCursor);
}

void reset() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD posicion = {0, 0};
    SetConsoleCursorPosition(hConsole, posicion);
}

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon,dwPos);
}

void setColor(int color) {
    HANDLE pintura;
    pintura = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(pintura, color);
}