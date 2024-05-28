#include "Utils.h"
#include "EnemigoFinal.h"
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

//Configuración para generacion aleatoria
random_device rd;
mt19937 gen(rd());

//Metodo para mostrar el tablero por consola
void Utils::verTablero(string tablero[10][5]) {
    cout << "---------------------" << endl;
    //Iteramos la cantidad de filas
    for (int i = 0; i < 10; i++) {
        //Por cada fila, iteramos la cantidad de posiciones de columnas
        for (int j = 0; j < 5; j++) {
            //Mostramos el contenido de la cela en posicion tablero[i][j]
            cout << tablero[i][j];
        }
        //Si es el final de fila, cerramos con el último |, y añadimos una fila de separación
        cout << "|" << endl << "---------------------" << endl;
    }
}

//Metodo para generar un numero aleatorio en un rango entre min y max
int Utils::randNumber(int min, int max) {
    //Metodo para generar una distribución entre el minimo y el máximo
    uniform_int_distribution<> distrib(min, max);
    //De la distribución creada antes, generamos un numero
    return distrib(gen);
}

//Metodo para validar si una coordenada comparada con otra está vacía y está dentro del tablero
bool Utils::checkVacia(array<int, 2> cord1, array<int, 2> cord2) {
    //Se realizan las siguientes comprobaciones
    //Coordenada 1-Y no sea igual a coordenada 2-Y y Coordenada 1-X no sea igual a Coordenada 2-X
    //O que coordenada 1 esté fuera del tablero en coordenada Y o X
    //O que coordenada 2 esté fuera del tablero en coordenada Y o X
    if ((cord1[0] == cord2[0] && cord1[1] == cord2[1]) || cord1[0] < 0 || cord1[1] > 9 || cord2[0] < 0 || cord2[1] > 4) {
        //Si se cumple cualquiera de las condiciones, la coordenada no es válida y se retorna false
        return false;
    }
    else {
        //Si no se cumplen las condiciones, es decir la coordenada es vaída, se retorna true
        return true;
    }
}

//Metodo para buscar una posición vacía aleatoria del tablero sin contar la salida ni la guarida
array<int, 2> Utils::getPosicionVacia(const array<int, 2>& salida, const array<int, 2>& guarida) {
    //Declaramos la variable posición, que es un array de 2 posiciones, en la que generamos una fila aleatoria entre 0 y 9, y una columna aleatoria entre 0 y 4
    array<int, 2> posicion = { randNumber(0, 9), randNumber(0, 4) };
    //Validamos que la posición generada aleatoriamente sea correcta con la salida y la guarida
    if (checkVacia(posicion, salida) || checkVacia(posicion, guarida)) {
        //Si ambas validaciones son correctas, retornamos la posición generada
        return posicion;
    }
    else {
        //Si no es correcta, hacemos una llamada recursiva a getPosicionVacia, para que vuelva a generar una posición vacía valida
        return getPosicionVacia(salida, guarida);
    }
}

//Metodo para colocar a los enemigos en el tablero, teniendo en cuenta la salida y la guarida
vector<Personaje> Utils::colocarEnemigos(array<int, 2> salida, array<int, 2> guarida) {
    //Definimos un vector de Personaje para los enemigos (funcionamiento similar a ArrayList de java)
    vector<Personaje> enemigos;
    //Iteramos 4 veces para generar 4 enemigos
    for (int i = 0; i < 4; i++) {
        //Generamos una posición en la que se encontrará el enemigo
        array<int, 2> posicion = getPosicionVacia(salida, guarida);
        //Añadimos al vector de Personaje un nuevo enemigo con la posición generada
        enemigos.push_back(Personaje(10, 1, "Trol", posicion[0], posicion[1]));
    }
    //Retornamos el vector de Personaje enemigo
    return enemigos;
}

//Metodo para mover a los enemigos por el tablero
void Utils::moverEnemigos(vector<Personaje>& enemigos, array<int, 2> salida, array<int, 2> guarida) {
    //Iteramos en un foreach cada enemigo del vector de enemigos
    for (Personaje& j : enemigos) {
        //Por cada enemigo, ponemos una nueva posición, que está será la retornada por generarMovimientoAleatorio
        j.setPosicion(generarMovimientoAleatorio({ j.getPosY(), j.getPosX() }, salida, guarida));
    }
}

//Metodo para generar un movimiento aleatorio de un enemigo
array<int, 2> Utils::generarMovimientoAleatorio(array<int, 2> actual, array<int, 2> salida, array<int, 2> guarida) {
    //Definimos el movimiento del enemigo como un array de 2 posiciones
    array<int, 2> movimiento;
    //Modificamos la posición Y e X de la posición de manera aleatoria
    movimiento[0] = cambiarNumeroAleatorio(actual[0]);
    movimiento[1] = cambiarNumeroAleatorio(actual[1]);
    //Validamos que la posición es valida en comparacion con la salida y la guarida
    if (checkVacia(movimiento, salida) && checkVacia(movimiento, guarida)) {
        //Si es una posición válida la retornamos
        return movimiento;
    }
    else {
        //Si no es una posición válida, llamamos de manera recursiva al metodo generarMovimientoAleatorio y retornamos su resultado
        return generarMovimientoAleatorio(actual, salida, guarida);
    }
}

//Metodo para de un numero recibido, de manera alatoria, sumar +1, restar -1 o no hacer nada
int Utils::cambiarNumeroAleatorio(int numero) {
    //Metodo para generar una distribución entre 0 y 2
    uniform_int_distribution<> distrib(0, 2);
    // Generar un número aleatorio
    int decision = distrib(gen);
    // Decidir el nuevo valor basado en el número aleatorio
    if (decision == 0) {
        //Si la decision es 0, se resta 1
        return numero - 1;
    }
    else if (decision == 1) {
        //Si la decision es 1, se mantiene el numero original
        return numero;
    }
    else {
        //Si la decision es 2, se suma 1
        return numero + 1;
    }
}

//Movimiento para manejar el movimiento del jugador
void Utils::hacerMovimientoJugador(vector<Personaje>& enemigos, Personaje& jugador) {
    //Iteramos los enemigos que referencian al vector de main
    for (auto& enemigo : enemigos) {
        //Si la posición del enemigo es la misma que la del personaje se inicia el combate
        if (enemigo.getPosY() == jugador.getPosY() && enemigo.getPosX() == jugador.getPosX()) {
            cout << "Te encuentras con un trol salvaje:" << endl;
            //Definimos un boolean auxiliar para manejar la pelea con el enemigo
            bool pelea = true;
            //Mientras que pelea sea true, y el jugador o el enemigo estén vivos, es decir, tengan vida mayor que 0
            while (pelea && jugador.getVida() > 0 && enemigo.getVida() > 0) {
                //El jugador ataca al enemigo primero (un caballero es más fuerte que un troll de bosque)
                enemigo.recibirAtaque(jugador.getAtaque());
                //Si el ataque no ha matado al enemigo, es decir, tiene vida mayor que 0
                if (enemigo.getVida() > 0) {
                    //El jugador recibe un ataque del enemigo
                    jugador.recibirAtaque(enemigo.getAtaque());
                    //Se muestra el nombre de ambos y la vida de ambos a cada turno de la pelea
                    cout << jugador.getNombre() << ": " << jugador.getVida() << endl << "Trol: " << enemigo.getVida() << endl;
                }
                else {
                    //Si la vida del enemigo es menor o igual a 0 se acaba el combate
                    pelea = false;
                }
            }
        }
    }

    // Eliminamos enemigos con vida 0 usando iteradores
    enemigos.erase(remove_if(enemigos.begin(), enemigos.end(), [](Personaje& enemigo) {
        return enemigo.getVida() == 0;
        }), enemigos.end());
}

//Metodo para la pelea final
void Utils::finalBoss(Personaje& jugador) {
    //Creamos la variable del boss final
    //Si se quiere valancear, se modifica aquí
    EnemigoFinal boss = EnemigoFinal(2, 3, 30, 2, "Trol Jefe", 0, 0);
    // Valor aleatorio para seleccionar ataque especial
    uniform_int_distribution<> dist(1, 3);
    // Valor aleatorio para decidir quién ataca primero
    uniform_int_distribution<> turnoDist(1, 2);
    //Boolean auxiliar para manejar la pelea
    bool pelea = true;
    //Generamos el valor aleatorio del turno
    int turno = turnoDist(gen);
    //Bucle mientras que pelea sea true, y el jugador o el boss tengan vida diferente de 0
    while (pelea && jugador.getVida() != 0 && boss.getVida() != 0) {
        //Si el turno generado aleatorio es 1
        if (turno == 1) {
            // Turno del jugador
            //El jugador ataca al boss
            boss.recibirAtaque(jugador.getAtaque());
            //Mostramos en consola el resultado
            cout << jugador.getNombre() << " ataca al " << boss.getNombre() << " por " << jugador.getAtaque() << " de daño." << endl;
            cout << boss.getNombre() << " vida: " << boss.getVida() << endl;
            //Se cambia el turno al boss
            turno = 2;
        }
        else {
            //Turno del jefe final
            //Se genera aleatoriamente que ataque usara
            int tipoAtaque = dist(gen);
            //Variable auxiliar para almacenar el daño del boss
            int danio = 0;
            //Si es tipo ataque 1
            if (tipoAtaque == 1) {
                //Daño es el ataque base del boss
                danio = boss.getAtaque();
                //Se muestra en consola
                cout << boss.getNombre() << " usa ataque normal por " << danio << " de daño." << endl;
                //Si es tipo ataque 2
            }
            else if (tipoAtaque == 2) {
                //Daño es el ataque especial 1 del boss
                danio = boss.getAtaque1();
                //Se muestra en consola
                cout << boss.getNombre() << " usa ataque especial 1 por " << danio << " de daño." << endl;
            }
            else {
                //Si tipoAtaque es 3, daño es el ataque especial 2 del boss
                danio = boss.getAtaque2();
                //Se muestra en consola
                cout << boss.getNombre() << " usa ataque especial 2 por " << danio << " de daño." << endl;
            }
            //El jugador recibe el ataque generado
            jugador.recibirAtaque(danio);
            //Se muestra en pantalla
            cout << jugador.getNombre() << " vida: " << jugador.getVida() << endl;
            //Se cambia el turno al jugador
            turno = 1;
        }
        //Se espera 1 segundo para hacer la pelea más realista
        this_thread::sleep_for(chrono::seconds(1));
    }

    //Si la vida del jugador es diferente de 0, es decir está vivo
    if (jugador.getVida() != 0) {
        //Se muestra por consola que el jugador ha ganado
        cout << "¡" << jugador.getNombre() << " ha derrotado al " << boss.getNombre() << "!" << endl;
    }
    else {
        //Si no se cumple la condición, es decir el jugador ha muerto
        //Se muestra por consola
        cout << boss.getNombre() << " ha derrotado a " << jugador.getNombre() << "." << endl;
    }
}
