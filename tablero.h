#ifndef TABLERO_H
#define TABLERO_H
// Crea un tablero de 'filas' x 'columnas' y reserva la memoria necesaria
unsigned char* crearTablero(int filas, int columnas);
// Calcula la cantidad minima de bytes necesarios para el tablero
int bytesNecesarios(int filas, int columnas);
// Lee el valor (0-7) en la posicion (fila, columna)
int leerFicha(unsigned char* tablero, int fila, int columna, int columnas);
// Escribe un nuevo valor (0-7) en la posicion (fila, columna)
void escribirFicha(unsigned char* tablero, int fila, int columna, int columnas, int nuevoValor);
// Libera la memoria reservada para el tablero
void liberarTablero(unsigned char* tablero);
#endif // TABLERO_H
