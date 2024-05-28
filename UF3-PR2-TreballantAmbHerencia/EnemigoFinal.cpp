#include "EnemigoFinal.h"

//Constructor para la clase EnemigoFinal
EnemigoFinal::EnemigoFinal(int ataque1, int ataque2, int vida, int ataque, std::string nombre, int posicionX, int posicionY) : Personaje(vida, ataque, nombre, posicionX, posicionY) {}

//Getter ataque 1
int EnemigoFinal::getAtaque1() {
    return ataque1;
}

//Getter ataque 2
int EnemigoFinal::getAtaque2() {
    return ataque2;
}