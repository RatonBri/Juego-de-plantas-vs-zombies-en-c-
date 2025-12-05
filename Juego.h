#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Constantes globales
const int FILAS = 5;
const int COLS = 10;

class Entidad;

class Juego {
private:
    Entidad* tablero[FILAS][COLS];
    int soles;
    int casaHP;
    int oleada;
    int turno;

    string jugador;
    int solesGanados;
    int zombiesMuertos;

public:
    Juego();
    ~Juego();

    void iniciar(const string& nombre, int maxOleadas);
    void guardarStats(bool victoria) const;

    // Métodos de gestión de tablero
    void colocarEntidad(Entidad* e, int f, int c);
    void eliminarEntidad(int f, int c);
    void moverEntidad(int f1, int c1, int f2, int c2);
    Entidad* getEntidad(int f, int c) const;

    // Fases y turnos
    void faseColocacion();
    void ejecutarTurno(bool spawnear);
    void imprimirTablero() const;
    void spawnTurno();
    bool hayZombies() const;

    // Métodos de daño/efecto
    void hacerDano(int f, int c, int d); // <-- CORRECCIÓN: Ahora dice 'int c'
    void hacerDanoCasa(int d);
    void explosion3x3(int x, int y, int d);

    // Métodos de acceso
    void addSoles(int s) { soles += s; solesGanados += s; }
    int getSoles() const { return soles; }
    int getCasaHP() const { return casaHP; }
};

#endif


