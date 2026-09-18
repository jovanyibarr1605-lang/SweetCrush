#include <iostream>
#include "visualizacion.h"
#include "tablero.h"

using namespace std;

void mostrarFicha(int ficha) {
    switch (ficha) {

    case 0:
        cout << " ";
        break;

    case 1:
        cout << "\033[31mA\033[0m";
        break;
    
    case 2:
        cout << "\033[32mB\033[0m";
        break;
    
    case 3:
        cout << "\033[33mC\033[0m";
        break;

    case 4:
        cout << "\033[34mD\033[0m";
        break;

    case 5:
        cout << "\033[35mE\033[0m";
        break;

    case 6:
        cout << "\033[36mF\033[0m";
        break;

    case 7:
        cout << "\033[97m*\033[0m";
        break;
    
    default:
        cout << "?";
        break;
    }
}

void mostrarTablero(unsigned char* tablero, int filas, int columnas) {
    cout << "\n   ";

    for (int columna = 0; columna < columnas; columna++){
        if (columna + 1 < 10) {
            cout << " ";
        }

        cout << columna + 1 << " ";
    }

    cout << "\n";

    for (int fila = 0; fila < filas; fila++){
        if (fila + 1 < 10) {
            cout << " ";
        }

        cout << fila + 1 << " ";

        for (int columna = 0; columna < columnas; columna++) {
            int ficha = leerFicha(tablero, fila, columna, columnas);

            cout << " ";
            mostrarFicha(ficha);
            cout << " ";
        }

        cout << "\n";
    }
}

void mostrarBits(unsigned char* tablero, int filas, int columnas) {
    int bytes = bytesNecesarios(filas, columnas);

    cout << "\nBytes del tablero en binario: ";

    for (int byte = bytes - 1; byte >= 0; byte--) {
        for (int bit = 7; bit >= 0; bit--) {
            cout << ((tablero[byte] >> bit ) & 1);
        }

        cout << " ";
    }

    cout << "\n";
}

void mostrarEstado(int filas, int columnas, int puntaje, int eliminacionesUsuario, int fichasEliminadas, int combinaciones, int cascadas, int movimientosRestantes) {
    cout << "\n----------------------------------------\n";
    cout << "Tamano actual: " << filas << " filas x " << columnas << " columnas\n";
    cout << "Puntaje: " << puntaje << "\n";
    cout << "Eliminaciones del jugador: " << eliminacionesUsuario << "\n";
    cout << "Fichas eliminadas: " << fichasEliminadas << "\n";
    cout << "Combinaciones detectadas: " << combinaciones << "\n";
    cout << "Cascadas realizadas: " << cascadas << "\n";
    cout << "Movimientos restantes: " << movimientosRestantes << "\n";
    cout << "----------------------------------------\n";
}

void mostrarMenu() {
    cout << "\n============== MENU ==============\n";
    cout << "1. Seleccionar una ficha\n";
    cout << "2. Ver tablero con fichas\n";
    cout << "3. Ver tablero en binario\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}
