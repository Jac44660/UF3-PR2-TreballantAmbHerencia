#pragma once
#include <iostream>
#include <array>
#include <vector>

#include "Personaje.h"

using namespace std;

class Utils {
public:
    static void verTablero(std::string tablero[10][5]);
    static int randNumber(int min, int max);
    static array<int, 2> getPosicionVacia(const array<int, 2>& salida, const array<int, 2>& guarida);
    static bool checkVacia(array<int, 2> cord1, std::array<int, 2> cord2);
    static vector<Personaje> colocarEnemigos(array<int, 2> salida, array<int, 2> guarida);
    static void moverEnemigos(vector<Personaje>& enemigos, array<int, 2> salida, array<int, 2> guarida);
    static array<int, 2> generarMovimientoAleatorio(array<int, 2> actual, array<int, 2> salida, array<int, 2> guarida);
    static int cambiarNumeroAleatorio(int numero);
    static void hacerMovimientoJugador(vector<Personaje>& enemigos, Personaje& jugador);
    static void finalBoss(Personaje& jugador);
};
