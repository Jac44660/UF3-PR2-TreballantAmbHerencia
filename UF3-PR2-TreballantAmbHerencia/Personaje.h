#pragma once
#ifndef Personaje_h
#define Personaje_h

#include <iostream>

using namespace std;

class Personaje {
private:
    //Atributos de la clase Personaje
    int vida;
    int ataque;
    string nombre;
    int posicionX;
    int posicionY;

public:
    //Constructor con parametros
    Personaje(int vida, int ataque, string nombre, int posicionY, int posicionX);
    //Getters
    int getPosX();
    int getPosY();
    int getVida();
    int getAtaque();
    string getNombre();
    //Metodo recibir ataque
    void recibirAtaque(int ataque);
    //Metodo para poner una nueva posición al personaje
    void setPosicion(array<int, 2> posicion);
};

#endif