#include "combinaciones.h"
#include "tablero.h"

bool esFichaCombinable(int ficha) {
    return ficha >= 1 && ficha <= 6;
}

void marcarCombinacionesHorizontales(unsigned char* tablero, int filas, int columnas, unsigned char* marcas, int &combinacionesDetectadas) {
    for (int fila = 0; fila < filas; fila++) {
        int inicio = 0; 

        while (inicio < columnas) {
            int ficha = leerFicha(tablero, fila, inicio, columnas);
            int columna = inicio + 1;

            while (columna < columnas && esFichaCombinable(ficha) && leerFicha(tablero, fila, columna, columnas) == ficha) {
                columna ++;
            }

            int longitud = columna - inicio;

            if (esFichaCombinable(ficha) && longitud >= 3) {
                combinacionesDetectadas++;
                for (int columnaMarcada = inicio; columnaMarcada < columna; columnaMarcada++) {
                    marcas[fila * columnas + columnaMarcada] = 1;
                }
            }

            inicio = columna;
        }
    }
}

void marcarCombinacionesVerticales(unsigned char* tablero, int filas, int columnas, unsigned char* marcas, int &combinacionesDetectadas) {
    for (int columna = 0; columna < columnas; columna++) {
        int inicio = 0;

        while (inicio < filas) {
            int ficha = leerFicha(tablero, inicio, columna, columnas);
            int fila = inicio + 1;

            while (fila < filas && esFichaCombinable(ficha) && leerFicha(tablero, fila, columna, columnas) == ficha) {
                fila ++;
            }

            int longitud = fila - inicio;

            if (esFichaCombinable(ficha) && longitud >= 3) {
                combinacionesDetectadas++;
                for (int filaMarcada = inicio; filaMarcada < fila; filaMarcada++) {
                    marcas[filaMarcada * columnas + columna] = 1;
                }
            }

            inicio = fila;
        }
    }
}

int detectarYEliminarCombinaciones(unsigned char* tablero, int filas, int columnas, int &combinacionesDetectadas) {
    int cantidadPosiciones = filas * columnas;
    unsigned char* marcas = new unsigned char[cantidadPosiciones];

    for (int indice = 0; indice < cantidadPosiciones; indice++) {
        marcas[indice] = 0;
    }

    int combinacionesEnEstaRevision = 0;

    marcarCombinacionesHorizontales(tablero, filas, columnas, marcas, combinacionesEnEstaRevision);
    marcarCombinacionesVerticales(tablero, filas, columnas, marcas, combinacionesEnEstaRevision);

    combinacionesDetectadas += combinacionesEnEstaRevision;

    int eliminadas = 0;

    for (int indice = 0; indice < cantidadPosiciones; indice++) {
        if (marcas[indice] == 1) {
            int fila = indice / columnas;
            int columna = indice % columnas;

            escribirFicha(tablero, fila, columna, columnas, 0);
            eliminadas++;
        }
    }

    delete[] marcas;

    return eliminadas;
}