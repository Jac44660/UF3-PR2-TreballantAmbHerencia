#include <array>
#include "Personaje.h"

//Constructor para la clase Personaje
Personaje::Personaje(int vida, int ataque, std::string nombre, int posicionY, int posicionX) : vida(vida), ataque(ataque), nombre(nombre), posicionX(posicionX), posicionY(posicionY) {}

//Getter pos X
int Personaje::getPosX() {
    return posicionX;
}

//Getter pos Y
int Personaje::getPosY() {
    return posicionY;
}

//Getter vida
int Personaje::getVida() {
    return vida;
}

//Getter nombre
string Personaje::getNombre() {
    return nombre;
}

//Getter ataque
int Personaje::getAtaque() {
    return ataque;
}

//Metodo encargado de manejar la recepcion de daño
void Personaje::recibirAtaque(int ataque) {
    //Si el ataque deja por debajo de 0 o igual a 0 la vida del personaje
    //indica que este ha muerto. Lo mostramos por consola y por si es el caso
    //de que el ataque deja por debajo de 0 la vida del personaje, le ponemos valor 0
    if (vida - ataque <= 0) {
        cout << nombre << " ha muerto" << endl;
        vida = 0;
        //Si el ataque no deja por debajo de 0 al personaje, mostramos el daño que
        //recibe, y restamos a la vida el ataque recibido
    }
    else {
        cout << nombre << " recibe " << ataque << " de daño " << endl;
        vida = vida - ataque;
    }
}

//Metodo para cambiar la posicion del personaje, este recibe un array de tamaño 2,
//en el que la posición 0 es la coordenada Y, y la posición 1 es la coordenada x
void Personaje::setPosicion(array<int, 2> posicion) {
    this->posicionY = posicion[0];
    this->posicionX = posicion[1];
}