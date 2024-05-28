#include "Personaje.h"
#include "Utils.h"

using namespace std;

int main() {
    //Definimos el tablero de juego
    string tablero[10][5] = {
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "},
        {"|   ", "|   ", "|   ", "|   ", "|   "} };
    //Buscamos una posición aleatoria para la salida y la guarida. La salida siempre estará en la fila 0, y la guarida en la fila 9. Generamos un numero aleatorio para cada una de 0 a 4, para determinar la columna, y guardamos las coordenadas en un array
    array<int, 2> salida = { 0, Utils::randNumber(0, 4) };
    array<int, 2> guarida = { 9, Utils::randNumber(0, 4) };
    //Con la posición de la salida definida, colocamos s en el tablero en esas coordenadas
    tablero[salida[0]][salida[1]] = "| s ";
    tablero[guarida[0]][guarida[1]] = "| g "; //solo testing
    //Generamos las posiciones iniciales de los enemigos
    vector<Personaje> enemigos = Utils::colocarEnemigos(salida, guarida);
    //Iteramos todos los enemigos
    for (Personaje& p : enemigos) {
        //Por cada enemigo colocamos en el tablero una letra T de trol
        tablero[p.getPosY()][p.getPosX()] = "| T ";
    }
    //Definimos una variable para el nombre del jugador
    string nombreJugador;
    //Preguntamos el nombre por consola
    cout << "¿Cual es el nombre del valeroso guerrero que se adentrará en estos bosques tan peligrosos?" << endl;
    //Almacenamos el input del usuario en la variable nombreJugador
    cin >> nombreJugador;
    //Creamos un objeto de tipo Personaje con el nombre recibido y la posición en las coordenadas de salida
    Personaje jugador = Personaje(30, 2, nombreJugador, salida[0], salida[1]);
    //Variable auxiliar boolean para controlar la partida
    bool partidaEnCurso = true;
    //Mientras que la partida esté en curso
    while (partidaEnCurso) {
        //Mostramos el tablero
        Utils::verTablero(tablero);
        //Y mostramos la vida del jugador
        cout << jugador.getNombre() << ": " << jugador.getVida() << endl;
        //Definimos una variable auxiliar para almacenar el movimiento del jugador
        string movJugador;
        //Definimos una variable auxiliar para controlar si el movimiento introducido es valido o posible
        bool movJugadorValido = false;
        //Si la posición del jugador no es la salida, quitamos su posición en el tablero para pintar la nueva posición
        if (salida[0] != jugador.getPosY() || salida[1] != jugador.getPosX()) {
            tablero[jugador.getPosY()][jugador.getPosX()] = "|   ";
        }
        //Preguntamos la posición del jugador por consola
        cout << "¿En que dirección quieres moverte? (w, s, a o d)" << endl;
        //Mientras que el movimiento del jugador no sea valido
        while (movJugadorValido == false) {
            //Almancenamos el movimiento introducido por consola en la variable movJugador
            cin >> movJugador;
            //Si el movimiento es arriba
            if (movJugador == "w") {
                //Validamos si el movimiento es válido y posible con la posición actual del jugador, y la misma posición con -1 en Y
                if (Utils::checkVacia({ jugador.getPosY(), jugador.getPosX() }, { jugador.getPosY() - 1, jugador.getPosX() })) {
                    //Si la posición es posible y valida, la colocamos al jugador
                    jugador.setPosicion({ jugador.getPosY() - 1, jugador.getPosX() });
                    //Ponemos que el movimiento es valido
                    movJugadorValido = true;
                }
                //Si el movimiento es abajo
            }
            else if (movJugador == "s") {
                //Validamos si el movimiento es válido y posible con la posición actual del jugador, y la misma posición con +1 en Y
                if (Utils::checkVacia({ jugador.getPosY(), jugador.getPosX() }, { jugador.getPosY() + 1, jugador.getPosX() })) {
                    //Si la posición es posible y valida, la colocamos al jugador
                    jugador.setPosicion({ jugador.getPosY() + 1, jugador.getPosX() });
                    //Ponemos que el movimiento es valido
                    movJugadorValido = true;
                }
                //Si el movimiento es derecha
            }
            else if (movJugador == "d") {
                //Validamos si el movimiento es válido y posible con la posición actual del jugador, y la misma posición con +1 en X
                if (Utils::checkVacia({ jugador.getPosY(), jugador.getPosX() }, { jugador.getPosY(), jugador.getPosX() + 1 })) {
                    //Si la posición es posible y valida, la colocamos al jugador
                    jugador.setPosicion({ jugador.getPosY(), jugador.getPosX() + 1 });
                    //Ponemos que el movimiento es valido
                    movJugadorValido = true;
                }
                //Si el movimieto es izquierda
            }
            else if (movJugador == "a") {
                //Validamos si el movimiento es válido y posible con la posición actual del jugador, y la misma posición con -1 en X
                if (Utils::checkVacia({ jugador.getPosY(), jugador.getPosX() }, { jugador.getPosY(), jugador.getPosX() - 1 })) {
                    //Si la posición es posible y valida, la colocamos al jugador
                    jugador.setPosicion({ jugador.getPosY(), jugador.getPosX() - 1 });
                    //Ponemos que el movimiento es valido
                    movJugadorValido = true;
                }
            }
            else {
                //Si el movimiento no es válido lo mostramos por consola y repetimos el bucle
                cout << "Dirección no valida o no posible" << endl;
            }
        }
        //Pintamos en el tablero la posicion del jugador
        tablero[jugador.getPosY()][jugador.getPosX()] = "| J ";
        //Validamos si el jugador ha llegado a la guarida
        if (jugador.getPosY() == guarida[0] && jugador.getPosX() == guarida[1]) {
            //Llamamos al metodo finalBoss
            Utils::finalBoss(jugador);
            //Finalizamos la partida  poniendo partidaEnCurso a false
            partidaEnCurso = false;
            //Si no está en la guarida
        }
        else {
            //Se hace el movimiento del jugador
            Utils::hacerMovimientoJugador(enemigos, jugador);
            //Se limpia la posición antigua de los enemigos
            for (Personaje& p : enemigos) {
                tablero[p.getPosY()][p.getPosX()] = "|   ";
            }
            //Movemos a los enemigos en el tablero
            Utils::moverEnemigos(enemigos, salida, guarida);
            //Volvemos a pintar su posición en el tablero
            for (Personaje& p : enemigos) {
                tablero[p.getPosY()][p.getPosX()] = "| T ";
            }
        }
    }
    return 0;
}