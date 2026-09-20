#include <iostream>
#include "tablero.h"
#include "mecanicas.h"
#include "visualizacion.h"

int main()
{
    int filas, columnas;
    unsigned int semilla;

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

    std::cout << "Ingrese una semilla numerica: ";
    std::cin >> semilla;

    unsigned char* tablero = crearTablero(filas, columnas);
    int capacidadBytes = bytesNecesarios(filas, columnas);

    llenarTableroInicial(tablero, filas, columnas, semilla);

    int puntaje = 0;
    int eliminacionesUsuario = 0;
    int fichasEliminadas = 0;
    int combinacionesTotales = 0;
    int cascadasActuales = 0;
    int movimientosRestantes = 20;

    bool jugando = true;
    bool modoBinario = false;

    while (jugando && movimientosRestantes > 0)
    {
        if (modoBinario)
        {
            mostrarBits(tablero, filas, columnas);
        }
        else
        {
            mostrarTablero(tablero, filas, columnas);
        }

        mostrarEstado(filas, columnas, puntaje, eliminacionesUsuario, fichasEliminadas, combinacionesTotales, cascadasActuales, movimientosRestantes);
        mostrarMenu();

        int opcion;
        if (!(std::cin >> opcion))
        {
            jugando = false;
            break;
        }

        if (opcion == 1)
        {
            int fila, columna;
            std::cout << "Fila: ";
            std::cin >> fila;
            std::cout << "Columna: ";
            std::cin >> columna;

            fila--;
            columna--;

            if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
            {
                std::cout << "La posicion indicada no existe." << std::endl;
            }
            else
            {
                int valorFicha = leerFicha(tablero, fila, columna, columnas);

                if (valorFicha == 7)
                {
                    int tipoEstructura, accion;
                    bool accionRealizada = false;
                    int eliminadasEstructura = 0;

                    cascadasActuales = 0;

                    std::cout << "Fila(1) o Columna(2)? ";
                    std::cin >> tipoEstructura;
                    std::cout << "Agregar(1) o Eliminar(2)? ";
                    std::cin >> accion;

                    if (tipoEstructura == 1 && accion == 1)
                    {
                        accionRealizada = agregarFila(tablero, filas, columnas, capacidadBytes, fila, semilla);
                    }
                    else if (tipoEstructura == 1 && accion == 2)
                    {
                        if (filas > 5)
                        {
                            eliminadasEstructura = eliminarFila(tablero, filas, columnas, capacidadBytes, fila);
                            accionRealizada = eliminadasEstructura >= 0;
                        }
                        else
                        {
                            std::cout << "El tablero no puede tener menos de 5 filas." << std::endl;
                        }
                    }
                    else if (tipoEstructura == 2 && accion == 1)
                    {
                        accionRealizada = agregarColumna(tablero, filas, columnas, capacidadBytes, columna, semilla);
                    }
                    else if (tipoEstructura == 2 && accion == 2)
                    {
                        if (columnas > 5)
                        {
                            eliminadasEstructura = eliminarColumna(tablero, filas, columnas, capacidadBytes, columna);
                            accionRealizada = eliminadasEstructura >= 0;
                        }
                        else
                        {
                            std::cout << "El tablero no puede tener menos de 5 columnas." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "La opcion estructural no es valida." << std::endl;
                    }

                    if (accionRealizada)
                    {
                        if (eliminadasEstructura > 0)
                        {
                            eliminacionesUsuario++;
                            fichasEliminadas += eliminadasEstructura;
                        }

                        resolverCascadas(tablero, filas, columnas, fichasEliminadas, combinacionesTotales, cascadasActuales, semilla);

                        movimientosRestantes--;
                        puntaje = fichasEliminadas * 10;
                    }
                }
                else if (valorFicha >= 1 && valorFicha <= 6)
                {
                    cascadasActuales = 0;

                    escribirFicha(tablero, fila, columna, columnas, 0);
                    eliminacionesUsuario++;
                    fichasEliminadas++;

                    aplicarGravedad(tablero, filas, columnas);
                    rellenarEspaciosVacios(tablero, filas, columnas, semilla);
                    resolverCascadas(tablero, filas, columnas, fichasEliminadas, combinacionesTotales, cascadasActuales, semilla);

                    movimientosRestantes--;
                    puntaje = fichasEliminadas * 10;
                }
                else
                {
                    std::cout << "La posicion esta vacia." << std::endl;
                }
            }
        }
        else if (opcion == 2)
        {
            modoBinario = false;
        }
        else if (opcion == 3)
        {
            modoBinario = true;
        }
        else if (opcion == 4)
        {
            jugando = false;
        }
        else
        {
            std::cout << "La opcion no es valida." << std::endl;
        }
    }

    std::cout << "--- Juego terminado ---" << std::endl;

    if (modoBinario)
    {
        mostrarBits(tablero, filas, columnas);
    }
    else
    {
        mostrarTablero(tablero, filas, columnas);
    }

    mostrarEstado(filas, columnas, puntaje, eliminacionesUsuario, fichasEliminadas, combinacionesTotales, cascadasActuales, movimientosRestantes);

    liberarTablero(tablero);

    return 0;
}
