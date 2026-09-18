#include <iostream>
#include <ctime>
#include "tablero.h"
#include "mecanicas.h"
#include "visualizacion.h"

int main()
{
    unsigned int semilla = static_cast<unsigned int>(time(nullptr));

    int filas, columnas;

    std::cout << "Ingrese numero de filas (minimo 5): ";
    std::cin >> filas;
    std::cout << "Ingrese numero de columnas (minimo 5): ";
    std::cin >> columnas;

    while (filas < 5 || columnas < 5)
    {
        std::cout << "Las dimensiones minimas son 5x5. Intente de nuevo." << std::endl;
        std::cout << "Filas: ";
        std::cin >> filas;
        std::cout << "Columnas: ";
        std::cin >> columnas;
    }

    unsigned char* tablero = crearTablero(filas, columnas);
    int capacidadBytes = bytesNecesarios(filas, columnas);

    llenarTableroInicial(tablero, filas, columnas, semilla);

    int puntaje = 0;
    int eliminacionesUsuario = 0;
    int fichasEliminadas = 0;
    int combinacionesTotales = 0;
    int movimientosRestantes = 20;

    bool jugando = true;

    while (jugando && movimientosRestantes > 0)
    {
        mostrarEstado(filas, columnas, puntaje, eliminacionesUsuario, fichasEliminadas, combinacionesTotales, 0, movimientosRestantes);
        mostrarMenu();

        int opcion;
        std::cin >> opcion;

        if (opcion == 1) // Seleccionar una ficha
        {
            int f, c;
            std::cout << "Fila: ";
            std::cin >> f;
            std::cout << "Columna: ";
            std::cin >> c;

            int valorFicha = leerFicha(tablero, f, c, columnas);

            if (valorFicha == 7) // ficha especial
            {
                int tipoEstructura, accion, indice;
                std::cout << "Fila(1) o Columna(2)? ";
                std::cin >> tipoEstructura;
                std::cout << "Agregar(1) o Eliminar(2)? ";
                std::cin >> accion;
                std::cout << "Indice: ";
                std::cin >> indice;

                if (tipoEstructura == 1 && accion == 1)
                {
                    agregarFila(tablero, filas, columnas, capacidadBytes, indice, semilla);
                }
                else if (tipoEstructura == 1 && accion == 2)
                {
                    eliminarFila(tablero, filas, columnas, capacidadBytes, indice);
                    int cascadasTemp = 0;
                    resolverCascadas(tablero, filas, columnas, fichasEliminadas, combinacionesTotales, cascadasTemp, semilla);
                }
                else if (tipoEstructura == 2 && accion == 1)
                {
                    agregarColumna(tablero, filas, columnas, capacidadBytes, indice, semilla);
                }
                else if (tipoEstructura == 2 && accion == 2)
                {
                    eliminarColumna(tablero, filas, columnas, capacidadBytes, indice);
                    int cascadasTemp = 0;
                    resolverCascadas(tablero, filas, columnas, fichasEliminadas, combinacionesTotales, cascadasTemp, semilla);
                }
            }
            else if (valorFicha != 0) // ficha normal, no vacia
            {
                escribirFicha(tablero, f, c, columnas, 0);
                eliminacionesUsuario++;
                fichasEliminadas++;

                // Aplicar gravedad y relleno tras la eliminacion manual
                aplicarGravedad(tablero, filas, columnas);
                rellenarEspaciosVacios(tablero, filas, columnas, semilla);

                // Revisar si el relleno genero combinaciones y resolver cascadas
                int cascadasEstaJugada = 0;
                resolverCascadas(tablero, filas, columnas, fichasEliminadas, combinacionesTotales, cascadasEstaJugada, semilla);
            }

            movimientosRestantes--;
            puntaje = fichasEliminadas * 10; // criterio de puntuacion, ajustar segun se documente
        }
        else if (opcion == 2) // Ver tablero con fichas
        {
            mostrarTablero(tablero, filas, columnas);
        }
        else if (opcion == 3) // Ver tablero en binario
        {
            mostrarBits(tablero, filas, columnas);
        }
        else if (opcion == 4) // Salir
        {
            jugando = false;
        }
    }

    std::cout << "--- Juego terminado ---" << std::endl;
    mostrarEstado(filas, columnas, puntaje, eliminacionesUsuario, fichasEliminadas, combinacionesTotales, 0, movimientosRestantes);

    liberarTablero(tablero);

    return 0;
}
