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