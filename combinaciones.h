#ifndef COMBINACIONES_H
#define COMBINACIONES_H

bool esFichaCombinable(int ficha);

int detectarYEliminarCombinaciones(unsigned char* tablero, int filas, int columnas, int &combinacionesDetectadas);

#endif