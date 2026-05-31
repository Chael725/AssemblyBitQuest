#include <windows.h>

static void ocultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO aparCursor;
    aparCursor.dwSize = 10; 
    aparCursor.bVisible = FALSE; 
    SetConsoleCursorInfo(hCon, &aparCursor);
}

static void reset() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD posicion = {3, 3};
    SetConsoleCursorPosition(hConsole, posicion);
}

static void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon,dwPos);
}

static void setColor(int color) {
    HANDLE pintura;
    pintura = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(pintura, color);
}

static void marco(){
    int j,k;

    setColor(5);

    for (int i = 3 ; i < 23 ; i++){
        gotoxy(i , 2);
        printf("%c",205);
        gotoxy(i , 23);
        printf("%c",205);
    }
    for (int i = 3 ; i < 23 ; i++){
        gotoxy(2 , i);
        printf("%c",186);
        gotoxy(23 , i);
        printf("%c",186);
    }

    gotoxy(2 , 2);//Esquina sup izq
    printf("%c",201);
    gotoxy(2 , 23); //Esquina inf izq
    printf("%c",200);
    gotoxy(23 , 2); //Esquina sup der
    printf("%c",187);
    gotoxy(23 , 23); //Esquina inf der
    printf("%c",188);

    setColor(7);
}