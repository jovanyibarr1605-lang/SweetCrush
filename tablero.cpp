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

unsigned char* agregarFila(unsigned char* tablero, int filas, int columnas, int filaInsertar, int valorDefecto)
{
    int nuevasFilas = filas + 1;
    int nuevoBytes = bytesNecesarios(nuevasFilas, columnas);
    unsigned char* nuevoTablero = new unsigned char[nuevoBytes + 1];

    for (int i = 0; i < nuevoBytes + 1; i++)
    {
        nuevoTablero[i] = 0;
    }

    for (int f = 0; f < filaInsertar; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f, c, columnas, valor);
        }
    }

    for (int c = 0; c < columnas; c++)
    {
        escribirFicha(nuevoTablero, filaInsertar, c, columnas, valorDefecto);
    }

    for (int f = filaInsertar; f < filas; f++)
    {
        for (int c = 0; c < columnas; c++)
        {
            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f + 1, c, columnas, valor);
        }
    }

    delete[] tablero;
    return nuevoTablero;
}

unsigned char* eliminarFila(unsigned char* tablero, int filas, int columnas, int filaEliminar)
{
    int nuevasFilas = filas - 1;
    int nuevoBytes = bytesNecesarios(nuevasFilas, columnas);
    unsigned char* nuevoTablero = new unsigned char[nuevoBytes + 1];

    for (int i = 0; i < nuevoBytes + 1; i++)
    {
        nuevoTablero[i] = 0;
    }

    int filaDestino = 0;

    for (int f = 0; f < filas; f++)
    {
        if (f == filaEliminar)
        {
            continue;
        }

        for (int c = 0; c < columnas; c++)
        {
            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, filaDestino, c, columnas, valor);
        }

        filaDestino++;
    }

    delete[] tablero;
    return nuevoTablero;
}
unsigned char* agregarColumna(unsigned char* tablero, int filas, int columnas, int columnaInsertar, int valorDefecto)
{
    int nuevasColumnas = columnas + 1;
    int nuevoBytes = bytesNecesarios(filas, nuevasColumnas);
    unsigned char* nuevoTablero = new unsigned char[nuevoBytes + 1];

    for (int i = 0; i < nuevoBytes + 1; i++)
    {
        nuevoTablero[i] = 0;
    }

    for (int f = 0; f < filas; f++)
    {
        for (int c = 0; c < columnaInsertar; c++)
        {
            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f, c, nuevasColumnas, valor);
        }

        escribirFicha(nuevoTablero, f, columnaInsertar, nuevasColumnas, valorDefecto);

        for (int c = columnaInsertar; c < columnas; c++)
        {
            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f, c + 1, nuevasColumnas, valor);
        }
    }

    delete[] tablero;
    return nuevoTablero;
}

unsigned char* eliminarColumna(unsigned char* tablero, int filas, int columnas, int columnaEliminar)
{
    int nuevasColumnas = columnas - 1;
    int nuevoBytes = bytesNecesarios(filas, nuevasColumnas);
    unsigned char* nuevoTablero = new unsigned char[nuevoBytes + 1];

    for (int i = 0; i < nuevoBytes + 1; i++)
    {
        nuevoTablero[i] = 0;
    }

    for (int f = 0; f < filas; f++)
    {
        int columnaDestino = 0;

        for (int c = 0; c < columnas; c++)
        {
            if (c == columnaEliminar)
            {
                continue;
            }

            int valor = leerFicha(tablero, f, c, columnas);
            escribirFicha(nuevoTablero, f, columnaDestino, nuevasColumnas, valor);
            columnaDestino++;
        }
    }

    delete[] tablero;
    return nuevoTablero;
}