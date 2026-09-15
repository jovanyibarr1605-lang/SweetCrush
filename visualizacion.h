#ifndef VISUALIZACION_H
#define VISUALIZACION_H

void mostrarTablero(unsigned char* tablero, int filas, int columnas);

void mostrarBits(unsigned char* tablero, int filas, int columnas);

void mostrarEstado(int filas, int columnas, int puntaje, int eliminacionesUsuario, int fichasEliminadas, int combinaciones, int cascadas, int movimientosRestantes);

void mostrarMenu();

#endif