#ifndef MECANICAS_H
#define MECANICAS_H

int generarFichaAleatoria(unsigned int &semilla);

void llenarTableroInicial(unsigned char* tablero, int filas, int columnas, unsigned int &semilla);

void aplicarGravedad(unsigned char* tablero, int filas, int columnas);

void rellenarEspaciosVacios(unsigned char* tablero, int filas, int columnas, unsigned int &semilla);

int resolverCascadas(unsigned char* tablero, int filas, int columnas, int &fichasEliminadas, int &combinaciones, int &cascadas, unsigned int &semilla);

bool agregarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidadBytes, int posicion, unsigned int &semilla);

bool agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidadBytes, int posicion, unsigned int &semilla);

int eliminarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidadBytes, int filaEliminar);

int eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidadBytes, int columnaEliminar);

#endif