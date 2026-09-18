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
// Inserta una fila nueva en 'filaInsertar', desplazando las filas siguientes; retorna el nuevo puntero
unsigned char* agregarFila(unsigned char* tablero, int filas, int columnas, int filaInsertar, int valorDefecto);
// Elimina la fila 'filaEliminar', desplazando las filas siguientes hacia arriba; retorna el nuevo puntero
unsigned char* eliminarFila(unsigned char* tablero, int filas, int columnas, int filaEliminar);
// Inserta una columna nueva en 'columnaInsertar' en todas las filas; retorna el nuevo puntero
unsigned char* agregarColumna(unsigned char* tablero, int filas, int columnas, int columnaInsertar, int valorDefecto);
// Elimina la columna 'columnaEliminar' de todas las filas; retorna el nuevo puntero
unsigned char* eliminarColumna(unsigned char* tablero, int filas, int columnas, int columnaEliminar);
#endif // TABLERO_H
