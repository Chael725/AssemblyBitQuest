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
extern int validar_movimiento(char* mapa, int columnas, int fila, int columna);
extern int calcular_puntaje(int monedas, int pasos, int niveles);

void copiar_mapa(char origen[FIL][COL+1], char destino[FIL][COL+1]) {
    for(int i = 0; i < FIL; i++) {
        for(int j = 0; j < COL + 1; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

int main() {
    system("mode con: cols=140 lines=55");
    system("chcp 437 > nul");
    ocultarCursor();

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

            if (nivel == 1) {
                copiar_mapa(mapa1, mapa_actual);
            } else if (nivel == 2) {
                copiar_mapa(mapa2, mapa_actual);
            } else if (nivel == 3) {
                copiar_mapa(mapa3, mapa_actual);
            }

            colocar_monedas(mapa_actual);
            colocar_enemigos(mapa_actual);
            colocar_llave(mapa_actual);

            int totalEnemigos = 0;
            int totalLlaves = 0;
            int totalMonedas = 0;
            contar_entidades((char*)mapa_actual, &totalEnemigos, &totalLlaves, &totalMonedas);

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

                    if (validar_movimiento((char*)mapa_actual, COL + 1, nuevaFila, nuevaColumna) == 1) {

                        if (llave && playing && mapa_actual[nuevaFila][nuevaColumna] == 'D'){
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        } else if (playing && mapa_actual[nuevaFila][nuevaColumna] == 'K') {
                            llave = true;
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        } else if (playing && mapa_actual[nuevaFila][nuevaColumna] == 'M') {
                            monedasRecogidas++;
                            monedasRecogidasTotales++;
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        } else if (playing && (mapa_actual[nuevaFila][nuevaColumna] == 'O' || mapa_actual[nuevaFila][nuevaColumna] == 'I')) {
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                            playing = 0;
                        } else if (playing && mapa_actual[nuevaFila][nuevaColumna] == '&') {
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                            playing = 0;
                        } else if (playing && mapa_actual[nuevaFila][nuevaColumna] == 'E') {
                            nivel_ganado = true;
                            nivelesCompletados++;

                            puntajeFinal = calcular_puntaje(monedasRecogidasTotales, pasosTotales, nivelesCompletados);

                            system("cls");
                            printf("=========================================\n");
                            printf("Nivel %d completado\n", nivel);
                            printf("Monedas recolectadas: %d / %d\n", monedasRecogidas, totalMonedas);
                            printf("Pasos realizados: %ld\n", pasos);
                            printf("Puntaje actual: %d\n", puntajeFinal);
                            printf("=========================================\n");
                            printf("\nPresiona cualquier tecla para continuar...");
                            _getch();

                            nivel++;

                            if (nivel == 2) {
                                int tEn, tLl, tMo;
                                char m2_aux[FIL][COL+1];
                                copiar_mapa(mapa2, m2_aux);
                                colocar_monedas(m2_aux);
                                contar_entidades((char*)m2_aux, &tEn, &tLl, &tMo);
                                monedasTotalesJuego += tMo;
                            } else if (nivel == 3) {
                                int tEn, tLl, tMo;
                                char m3_aux[FIL][COL+1];
                                copiar_mapa(mapa3, m3_aux);
                                colocar_monedas(m3_aux);
                                contar_entidades((char*)m3_aux, &tEn, &tLl, &tMo);
                                monedasTotalesJuego += tMo;
                            } else if (nivel > 3) {
                                puntajeFinal = calcular_puntaje(monedasRecogidasTotales, pasosTotales, nivelesCompletados);
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
                        } else if (playing && mapa_actual[nuevaFila][nuevaColumna] != 'D' && mapa_actual[nuevaFila][nuevaColumna] != '=') {
                            mapa_actual[jugadorFila][jugadorColumna] = '.';
                            jugadorFila = nuevaFila;
                            jugadorColumna = nuevaColumna;
                            mapa_actual[jugadorFila][jugadorColumna] = 'P';
                        }
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

                puntajeFinal = calcular_puntaje(monedasRecogidasTotales, pasosTotales, nivelesCompletados);

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
            }
        }
    }

    return 0;
}
