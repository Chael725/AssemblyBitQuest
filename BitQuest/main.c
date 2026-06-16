#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> 
#include <ctype.h>
#include <time.h>
#include "monedasLlave.h"
#include "enemigos.h"
#include "canones.h"
#include "menu.h"
#include "musica.h"


extern void contar_entidades(char* mapa, int* c_enemigos, int* c_llaves, int* c_monedas);
extern int detectar_objeto(char* mapa, int columnas, int fila, int columna, char objeto);
extern int contar_celdas_libres(char* mapa, int total_celdas);

void copiar_mapa(char origen[FIL][COL+1], char destino[FIL][COL+1]) {
    for(int i = 0; i < FIL; i++) {
        for(int j = 0; j < COL + 1; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

int cargar_mapa_desde_archivo(const char* nombre_archivo, char destino[FIL][COL+1]) {
    FILE *archivo = fopen(nombre_archivo, "r"); // Abre el archivo en modo lectura
    
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombre_archivo);
        return 0; // Falla
    }

    for (int i = 0; i < FIL; i++) {
        // Lee hasta COL + 2 para absorber posibles saltos de línea (\n o \r\n)
        if (fgets(destino[i], COL + 2, archivo) == NULL) {
            break; 
        }
        
        // Limpiamos los saltos de línea ocultos que Windows o Linux puedan agregar
        for(int j = 0; j < COL + 2; j++){
            if(destino[i][j] == '\n' || destino[i][j] == '\r'){
                destino[i][j] = '\0';
                break;
            }
        }
    }

    fclose(archivo);
    return 1; // Éxito
}

int main() {
    system("mode con: cols=140 lines=55");
    system("chcp 437 > nul");
    ocultarCursor();

    // --- VARIABLES DE AUDIO DECLARADAS AL INICIO DEL MAIN ---
    // Al ponerlas aquí con static, conservan su valor durante todo el ciclo de vida del juego
    static int volActual = 500; 
    static bool muteado = false;

    int eleccionMusica = 1; 
    char enter = 0;

    while (enter != 13) { // 13 es el codigo ASCII de la tecla ENTER.

        reproducir_musica(eleccionMusica); 

        system("cls");
        printf("=========================================\n");
        printf("       SELECCIONA LA MUSICA DE FONDO     \n");
        printf("=========================================\n");
        
        // Indicamos cual se selecciono con los **.
        if (eleccionMusica == 1) printf(" [1] * Cancion Arely *\n");
        else printf(" [1]   Cancion Arely\n");
        
        if (eleccionMusica == 2) printf(" [2] * Cancion Mossbyte Maze *\n");
        else printf(" [2]   Cancion Mossbyte Maze\n"); 
        printf("=========================================\n");
        printf("Presiona [ENTER] para confirmar e iniciar juego.");

        enter = _getch(); 
        
        if (enter == '1') { 
            eleccionMusica = 1;
            detener_musica();            // Apaga la canción actual.
            reproducir_musica(eleccionMusica); // Reproduce Cancion Arely.
        }

        else if (enter == '2') { 
            eleccionMusica = 2;
            detener_musica();            // Apaga la canción actual.
            reproducir_musica(eleccionMusica); // Reproduce Cancion Mossbyte Maze.
        }
    }

    long int pasosTotales = 0;
    int monedasTotalesJuego = 0;
    int monedasRecogidasTotales = 0;
    int nivelesCompletados = 0;
    int puntajeFinal = 0;

    char input;

    while (1) {
        system("cls");
        menu(input);
        system("cls");

        pasosTotales = 0;
        monedasTotalesJuego = 0;
        monedasRecogidasTotales = 0;
        nivelesCompletados = 0;
        puntajeFinal = 0;

        int nivel = 1;
        int juego_activo = 1; 

        while(juego_activo && nivel <= 3) {
            char mapa_actual[FIL][COL+1]; 

            
        int mapaCargado = 0;
        if (nivel == 1) {
            mapaCargado = cargar_mapa_desde_archivo("mapa1.txt", mapa_actual);
        } else if (nivel == 2) {
            mapaCargado = cargar_mapa_desde_archivo("mapa2.txt", mapa_actual);
        } else if (nivel == 3) {
            mapaCargado = cargar_mapa_desde_archivo("mapa3.txt", mapa_actual);
        }

        if (!mapaCargado) {
            printf("Faltan los archivos de mapa. Saliendo...\n");
            Sleep(2000);
            return 1;
        }

            colocar_monedas(mapa_actual);
            colocar_enemigos(mapa_actual);
            colocar_llave(mapa_actual);

            int totalEnemigos = 0;
            int totalLlaves = 0;
            int totalMonedas = 0;
            contar_entidades((char*)mapa_actual, &totalEnemigos, &totalLlaves, &totalMonedas);

            int celdasLibres = contar_celdas_libres((char*)mapa_actual, FIL * (COL + 1));
            
            if (pasosTotales == 0 && nivel == 1) {
                monedasTotalesJuego = totalMonedas; 
            }

            bool llave = false;
            long int pasos = 0;
            int monedasRecogidas = 0;
            int puntosKill = 0;
            int jugadorFila = 1;
            int jugadorColumna = 1;
            int playing = 1; 
            bool nivel_ganado = false; 
            char mira = 'D';

            clock_t disparo = clock();
            clock_t movBala = clock();

            system("cls");
            marco();

            while (playing) {
                setColor(7);

                gotoxy(30, 3);
                printf("Nivel: %d", nivel);

                gotoxy(30, 4);
                if (llave) {
                    printf("Llave: Si");
                } else {
                    printf("Llave: No");
                }

                gotoxy(30, 5);
                printf("Pasos: %ld", pasos);

                gotoxy(30, 6);
                printf("Monedas: %d/%d", monedasRecogidas, totalMonedas);

                gotoxy(30, 7);
                printf("Celdas libres: %d   ", celdasLibres);

                gotoxy(30, 9);
                printf("=======================");
                gotoxy(30, 10);
                if (muteado) printf("[M] Musica: MUTEADO    ");
                else printf("[M] Musica: SONANDO    ");
                gotoxy(30, 11);
                printf("[O] Bajar Volumen      ");
                gotoxy(30, 12);
                printf("[P] Subir Volumen      ");
                gotoxy(30, 13);
                printf("=======================");

                clock_t tiempoActual = clock();

                if ((tiempoActual - movBala) >= 300) { 
                    mover_proyectiles(mapa_actual, &playing, jugadorFila, jugadorColumna);
                    movBala = tiempoActual;
                    
                    reset();
                    imprimir_ventana(mapa_actual, jugadorFila, jugadorColumna);
                }

                if ((tiempoActual - disparo) >= 2000) {
                    generar_proyectiles(mapa_actual, &playing); 
                    disparo = tiempoActual;
                }
            
                if (_kbhit()) { 
                    input = toupper(_getch()); 

                    int nuevaFila = jugadorFila;
                    int nuevaColumna = jugadorColumna;


                    if (input == 'W') { nuevaFila--; mira = 'W'; pasos++; pasosTotales++; }
                    else if (input == 'S') { nuevaFila++; mira = 'S'; pasos++; pasosTotales++; }
                    else if (input == 'A') { nuevaColumna--; mira = 'A'; pasos++; pasosTotales++; }
                    else if (input == 'D') { nuevaColumna++; mira = 'D'; pasos++; pasosTotales++; }
                    else if (input == 'Q') {
                        playing = 0;
                        juego_activo = 0; 
                        break;
                    }else if (input == 'O') {  
                        volActual -= 100; 
                        if (volActual < 0) volActual = 0; 
                        cambiar_volumen(volActual);
                    }
                    else if (input == 'P') { 
                        volActual += 100; 
                        if (volActual > 1000) volActual = 1000; 
                        cambiar_volumen(volActual);
                    }else if (input == 'M') { 
                        if (!muteado) {
                            mutear_musica(); 
                            muteado = true;
                        } else {
                            desmutear_musica(volActual); 
                            muteado = false;
                        }
                    }

                    else if (input == 'E') {
                        if (mira == 'W') {
                            if (mapa_actual[jugadorFila - 1][jugadorColumna] == '&') { mapa_actual[jugadorFila - 1][jugadorColumna] = '.'; puntosKill += 5; }
                            if (mapa_actual[jugadorFila - 1][jugadorColumna] == '.') mapa_actual[jugadorFila - 1][jugadorColumna] = '|';
                        }
                        else if (mira == 'S') {
                            if (mapa_actual[jugadorFila + 1][jugadorColumna] == '&') { mapa_actual[jugadorFila + 1][jugadorColumna] = '.'; puntosKill += 5; }
                            if (mapa_actual[jugadorFila + 1][jugadorColumna] == '.') mapa_actual[jugadorFila + 1][jugadorColumna] = '|';
                        }
                        else if (mira == 'A') {
                            if (mapa_actual[jugadorFila][jugadorColumna - 1] == '&') { mapa_actual[jugadorFila][jugadorColumna - 1] = '.'; puntosKill += 5; }
                            if (mapa_actual[jugadorFila][jugadorColumna - 1] == '.') mapa_actual[jugadorFila][jugadorColumna - 1] = '-';
                        }
                        else if (mira == 'D') {
                            if (mapa_actual[jugadorFila][jugadorColumna + 1] == '&') { mapa_actual[jugadorFila][jugadorColumna + 1] = '.'; puntosKill += 5; }
                            if (mapa_actual[jugadorFila][jugadorColumna + 1] == '.') mapa_actual[jugadorFila][jugadorColumna + 1] = '-';
                        }
                        
                        reset();
                        imprimir_ventana(mapa_actual, jugadorFila, jugadorColumna);
                        Sleep(200); 
                        if (mapa_actual[jugadorFila - 1][jugadorColumna] == '|') mapa_actual[jugadorFila - 1][jugadorColumna] = '.';
                        if (mapa_actual[jugadorFila + 1][jugadorColumna] == '|') mapa_actual[jugadorFila + 1][jugadorColumna] = '.';
                        if (mapa_actual[jugadorFila][jugadorColumna - 1] == '-') mapa_actual[jugadorFila][jugadorColumna - 1] = '.';
                        if (mapa_actual[jugadorFila][jugadorColumna + 1] == '-') mapa_actual[jugadorFila][jugadorColumna + 1] = '.';
                    }

                    if (llave && playing && detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'D')){
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                    } else if (playing && detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'K')) {
                        llave = true;
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                    } else if (playing && detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'M')) {
                        monedasRecogidas++;
                        monedasRecogidasTotales++;
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                    } else if (playing && (detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'O') || detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'I'))) {
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        playing = 0; 
                    } else if (playing && detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, '&')) {
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        playing = 0; 
                    } else if (playing && detectar_objeto((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna, 'E')) {
                        nivel_ganado = true; 
                        system("cls");
                        printf("=========================================\n");
                        printf("Nivel %d completado\n", nivel);
                        printf("Monedas recolectadas: %d / %d\n", monedasRecogidas, totalMonedas);
                        printf("Pasos realizados: %ld\n", pasos);
                        printf("=========================================\n");
                        printf("\nPresiona cualquier tecla para continuar...");
                        _getch();

                        nivelesCompletados++;
                        if (totalMonedas > 0) {
                            puntajeFinal += (monedasRecogidas * 50) / totalMonedas;
                        }
                        puntajeFinal += puntosKill;

                        nivel++; 

                        if (nivel == 2) {
                            int tEn, tLl, tMo;
                            char m2_aux[FIL][COL+1];
                            // Cambiamos copiar_mapa por la lectura del archivo .txt
                            cargar_mapa_desde_archivo("mapa2.txt", m2_aux);
                            colocar_monedas(m2_aux);
                            contar_entidades((char*)m2_aux, &tEn, &tLl, &tMo);
                            monedasTotalesJuego += tMo;
                        } else if (nivel == 3) {
                            int tEn, tLl, tMo;
                            char m3_aux[FIL][COL+1];
                            // Cambiamos copiar_mapa por la lectura del archivo .txt
                            cargar_mapa_desde_archivo("mapa3.txt", m3_aux);
                            colocar_monedas(m3_aux);
                            contar_entidades((char*)m3_aux, &tEn, &tLl, &tMo);
                            monedasTotalesJuego += tMo;
                        } else if (nivel > 3) {
                            system("cls");
                            printf("=========================================\n");
                            printf("Juego completado\n");
                            printf("Monedas totales recolectadas: %d / %d\n", monedasRecogidasTotales, monedasTotalesJuego);
                            printf("Pasos totales: %ld\n", pasosTotales);
                            printf("Niveles completados: %d\n", nivelesCompletados);
                            printf("Puntaje final: %d\n", puntajeFinal);
                            printf("=========================================\n");
                            printf("\nPresiona cualquier tecla para regresar al menu principal...");
                            _getch();
                            juego_activo = 0;
                        }

                        playing = 0; 
                        break; 
                    } else if (playing && mapa_actual[nuevaFila][nuevaColumna] != '#' && mapa_actual[nuevaFila][nuevaColumna] != 'D' && mapa_actual[nuevaFila][nuevaColumna] != '=') {
                        mapa_actual[jugadorFila][jugadorColumna] = '.';
                        jugadorFila = nuevaFila;
                        jugadorColumna = nuevaColumna;
                        mapa_actual[jugadorFila][jugadorColumna] = 'P';
                    }

                    if (playing) {
                        mover_enemigos(mapa_actual, &playing, jugadorFila, jugadorColumna);
                    }

                    if (playing) {
                        reset();
                        imprimir_ventana(mapa_actual, jugadorFila, jugadorColumna);
                    }
                }
            }

            if (juego_activo && nivel <= 3 && !nivel_ganado) {
                system("cls");
                printf("=========================================\n");
                printf("               GAME OVER                 \n");
                printf("=========================================\n");
                printf("Monedas totales recolectadas: %d / %d\n", monedasRecogidasTotales, monedasTotalesJuego);
                printf("Pasos totales: %ld\n", pasosTotales);
                printf("Niveles completados: %d\n", nivelesCompletados);
                printf("Puntaje final: %d\n", puntajeFinal);
                printf("=========================================\n");
                printf("\nPresiona cualquier tecla para reiniciar el nivel %d...", nivel);
                _getch();
                
                monedasRecogidasTotales -= monedasRecogidas; 
                pasosTotales -= pasos;
            }
        }
    }

    detener_musica();
    return 0;
}