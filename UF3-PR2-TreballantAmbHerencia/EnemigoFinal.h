#pragma once
#include "Personaje.h"

//La clase EnemigoFinal extiende de Personaje
class EnemigoFinal : public Personaje {
private:
    //Atributos de la clase EnemigoFinal
    int ataque1;
    int ataque2;

public:
    //Constructor con atributos
    EnemigoFinal(int ataque1, int ataque2, int vida, int ataque, std::string nombre, int posicionX, int posicionY);
    //Getters
    int getAtaque1();
    int getAtaque2();
};
