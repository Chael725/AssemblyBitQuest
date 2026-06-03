#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "ventana.h"

void drakeArmar(){
    FILE *fileDrake;
    char drake[40]; 

    for(int i = 1; i < 12; i++){
        gotoxy(0, 0); 

        sprintf(drake, "drake_%d.txt", i);
        fileDrake = fopen(drake, "r");
        if(fileDrake == NULL){
            printf("Error al abrir el archivo %s", drake);
            continue;
        }
        
        char line[130];
        while(fgets(line, sizeof(line), fileDrake)){
            printf("%s", line);
        }

        fclose(fileDrake);
        
        Sleep(100); 
    }
    
}