#include "mecanicas.h"
#include "tablero.h"
#include "combinaciones.h"

using namespace std;

int generarFichaAleatoria(unsigned int &semilla){
    semilla = semilla * 1664525u + 1013904223u;

    return semilla %7u + 1;
}

void llenarTableroInicial(unsigned char* tablero, int filas, int columnas, unsigned int &semilla) {
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            escribirFicha(tablero, fila, columna, columnas, generarFichaAleatoria(semilla));
        }
    }
}

void aplicarGravedad(unsigned char* tablero, int filas, int columnas) {
    for (int columna = 0; columna < columnas; columna ++) {
        int filaDestino = filas - 1;

        for (int fila = filas - 1; fila >= 0; fila--) {
            int ficha = leerFicha(tablero, fila, columna, columnas);

            if (ficha != 0) {
                if (fila != filaDestino) {
                    escribirFicha(tablero, filaDestino, columna, columnas, ficha);
                    escribirFicha(tablero, fila, columna, columnas, 0);
                }

                filaDestino--;
            }
        }
    }
}

void rellenarEspaciosVacios(unsigned char* tablero, int filas, int columnas, unsigned int &semilla) {
    for (int columna = 0; columna < columnas; columna++) {
        for (int fila = 0; fila < filas; fila++) {
            int ficha = leerFicha(tablero, fila, columna, columnas);
             if (ficha == 0) {
                escribirFicha(tablero, fila, columna, columnas, generarFichaAleatoria(semilla));
             }
        }
    }
}

int resolverCascadas(unsigned char* tablero, int filas, int columnas, int &fichasEliminadas, int &combinaciones, int &cascadas, unsigned int &semilla) {
    int eliminadasTotal = 0;

    int eliminadasEnRevision = detectarYEliminarCombinaciones(tablero, filas, columnas, combinaciones);

    while (eliminadasEnRevision > 0) {
        eliminadasTotal += eliminadasEnRevision;
        fichasEliminadas += eliminadasEnRevision;

        aplicarGravedad(tablero, filas, columnas);
        rellenarEspaciosVacios(tablero, filas, columnas, semilla);

        eliminadasEnRevision = detectarYEliminarCombinaciones(tablero, filas, columnas, combinaciones);

        if (eliminadasEnRevision > 0) {
            cascadas++;
        }
    }

    return eliminadasTotal;
}

bool debeReducirMemoria(int bytesUsados, int capacidadBytes) {
    return bytesUsados * 100 < capacidadBytes * 65;
}

void limpiarMemoriaSobrante(unsigned char* tablero, int bitsUsados, int capacidadBytes) {
    int bytesUsados = (bitsUsados + 7) / 8;
    int bitsEnUltimoByte = bitsUsados % 8;

    if (bitsEnUltimoByte != 0) {
        unsigned char mascara = (1u << bitsEnUltimoByte) - 1u;

        tablero[bytesUsados - 1] &= mascara;
    }

    for (int byte = bytesUsados; byte <= capacidadBytes; byte++) {
        tablero[byte] = 0;
    }
}

bool agregarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidadBytes, int posicion, unsigned int &semilla) {
    if (posicion < 0 || posicion > filas) {
        return false;
    }

    int filasNuevas = filas + 1;
    int bytesNuevos = bytesNecesarios(filasNuevas, columnas);

    if (bytesNuevos > capacidadBytes) {
        unsigned char* nuevoTablero = crearTablero(filasNuevas, columnas);

        for (int fila = 0; fila < filas; fila++) {
            int filaNueva = fila;

            if (fila >= posicion) {
                filaNueva++;
            }

            for (int columna = 0; columna < columnas; columna++) {
                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(nuevoTablero, filaNueva, columna, columnas, ficha);
            }
        }

        for (int columna = 0; columna < columnas; columna++) {
            escribirFicha(nuevoTablero, posicion, columna, columnas, generarFichaAleatoria(semilla));
        }

        liberarTablero(tablero);
        tablero = nuevoTablero;
        capacidadBytes = bytesNuevos;
    }
    else {
        for (int fila = filas - 1; fila >= posicion; fila--) {
            for (int columna = columnas - 1; columna >= 0; columna--) {
                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(tablero, fila + 1, columna, columnas, ficha);
            }
        }

        for (int columna = 0; columna < columnas; columna++) {
            escribirFicha(tablero, posicion, columna, columnas, generarFichaAleatoria(semilla));
        }
    }

    filas = filasNuevas;

    return true;
}

bool agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidadBytes, int posicion, unsigned int &semilla) {
    if (posicion < 0 || posicion > columnas) {
        return false;
    }

    int columnasNuevas = columnas + 1;
    int bytesNuevos = bytesNecesarios(filas, columnasNuevas);

    if (bytesNuevos > capacidadBytes) {
        unsigned char* nuevoTablero = crearTablero(filas, columnasNuevas);

        for (int fila = 0; fila < filas; fila++) {
            for (int columna = 0; columna < columnas; columna++) {
                int columnaNueva = columna;

                if (columna >= posicion) {
                    columnaNueva++;
                }

                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(nuevoTablero, fila, columnaNueva, columnasNuevas, ficha);
            }
        }

        for (int fila = 0; fila < filas; fila++) {
            escribirFicha(nuevoTablero, fila, posicion, columnasNuevas, generarFichaAleatoria(semilla));
        }

        liberarTablero(tablero);
        tablero = nuevoTablero;
        capacidadBytes = bytesNuevos;
    }
    else {
        for (int fila = filas - 1; fila >= 0; fila--) {
            for (int columna = columnas - 1; columna >= posicion; columna--) {
                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(tablero, fila, columna + 1, columnasNuevas, ficha);
            }
        }

        for (int fila = 0; fila < filas; fila++) {
            escribirFicha(tablero, fila, posicion, columnasNuevas, generarFichaAleatoria(semilla));
        }
    }

    columnas = columnasNuevas;

    return true;
}

int eliminarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidadBytes, int filaEliminar) {
    if (filaEliminar < 0 || filaEliminar >= filas || filas <= 1) {
        return -1;
    }

    int eliminadas = 0;

    for (int columna = 0; columna < columnas; columna++) {
        int ficha = leerFicha(tablero, filaEliminar, columna, columnas);

        if (ficha != 0) {
            eliminadas++;
        }
    }

    for (int fila = filaEliminar + 1; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int ficha = leerFicha(tablero, fila, columna, columnas);

            escribirFicha(tablero, fila - 1, columna, columnas, ficha);
        }
    }

    filas--;

    int bytesUsados = bytesNecesarios(filas, columnas);

    if (debeReducirMemoria(bytesUsados, capacidadBytes)) {
        unsigned char* nuevoTablero = crearTablero(filas, columnas);

        for (int fila = 0; fila < filas; fila++) {
            for (int columna = 0; columna < columnas; columna++) {
                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(nuevoTablero, fila, columna, columnas, ficha);
            }
        }

        liberarTablero(tablero);
        tablero = nuevoTablero;
        capacidadBytes = bytesUsados;
    }
    else {
        limpiarMemoriaSobrante(tablero, filas * columnas * 3, capacidadBytes);
    }

    return eliminadas;
}

int eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidadBytes, int columnaEliminar) {
    if (columnaEliminar < 0 || columnaEliminar >= columnas || columnas <= 1) {
        return -1;
    }

    int eliminadas = 0;

    for (int fila = 0; fila < filas; fila++) {
        int ficha = leerFicha(tablero, fila, columnaEliminar, columnas);

        if (ficha != 0) {
            eliminadas++;
        }
    }

    int columnasNuevas = columnas - 1;

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = columnaEliminar + 1; columna < columnas; columna++) {
            int ficha = leerFicha(tablero, fila, columna, columnas);

            escribirFicha(tablero, fila, columna - 1, columnasNuevas, ficha);
        }
    }

    columnas = columnasNuevas;

    int bytesUsados = bytesNecesarios(filas, columnas);

    if (debeReducirMemoria(bytesUsados, capacidadBytes)) {
        unsigned char* nuevoTablero = crearTablero(filas, columnas);

        for (int fila = 0; fila < filas; fila++) {
            for (int columna = 0; columna < columnas; columna++) {
                int ficha = leerFicha(tablero, fila, columna, columnas);

                escribirFicha(nuevoTablero, fila, columna, columnas, ficha);
            }
        }

        liberarTablero(tablero);
        tablero = nuevoTablero;
        capacidadBytes = bytesUsados;
    }
    else {
        limpiarMemoriaSobrante(tablero, filas * columnas * 3, capacidadBytes);
    }

    return eliminadas;
}