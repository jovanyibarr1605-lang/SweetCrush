#include"tablero.h"

int bytesNecesarios(int filas, int columnas)
{
    int totalBits = 3 * filas * columnas;
    int totalBytes = (totalBits + 7) / 8;
    return totalBytes;
}
unsigned char* crearTablero(int filas, int columnas)
{
    int bytes = bytesNecesarios(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes + 1];

    for (int i = 0; i < bytes + 1; i++)
    {
        tablero[i] = 0;
    }

    return tablero;
}
int leerFicha(unsigned char* tablero, int fila, int columna, int columnas)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * 3;
    int byteInicial = bitInicial / 8;
    int offset = bitInicial % 8;

    int byteActual = tablero[byteInicial];
    int byteSiguiente = tablero[byteInicial + 1];

    int combinado = (byteSiguiente << 8) | byteActual;

    int ficha = (combinado >> offset) & 0x07;

    return ficha;
}
void escribirFicha(unsigned char* tablero, int fila, int columna, int columnas, int nuevoValor)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * 3;
    int byteInicial = bitInicial / 8;
    int offset = bitInicial % 8;

    int byteActual = tablero[byteInicial];
    int byteSiguiente = tablero[byteInicial + 1];

    int combinado = (byteSiguiente << 8) | byteActual;

    int mascara = 0x07 << offset;
    combinado = combinado & ~mascara;
    combinado = combinado | ((nuevoValor & 0x07) << offset);

    tablero[byteInicial] = combinado & 0xFF;
    tablero[byteInicial + 1] = (combinado >> 8) & 0xFF;
}
void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}
