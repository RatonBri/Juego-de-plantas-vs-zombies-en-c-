#include "Juego.h"
#include "Planta.h"
#include "Zombies.h"
#include "funciones.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

bool cancelar_partida = false;

Juego::Juego()
    : soles(200), casaHP(10), oleada(1), turno(0),
      solesGanados(0), zombiesMuertos(0)
{
    srand(time(NULL));
    for (int f = 0; f < FILAS; f++)
        for (int c = 0; c < COLS; c++)
            tablero[f][c] = nullptr;
}

Juego::~Juego() {
    for (int f = 0; f < FILAS; f++)
        for (int c = 0; c < COLS; c++)
            if (tablero[f][c])
                delete tablero[f][c];
}

void Juego::colocarEntidad(Entidad* e, int f, int c) { tablero[f][c] = e; }
void Juego::moverEntidad(int f1, int c1, int f2, int c2) {
    tablero[f2][c2] = tablero[f1][c1];
    tablero[f1][c1] = nullptr;
    tablero[f2][c2]->setPos(c2, f2);
}
Entidad* Juego::getEntidad(int f, int c) const {
    if (f < 0 || f >= FILAS || c < 0 || c >= COLS) return nullptr;
    return tablero[f][c];
}

void Juego::eliminarEntidad(int f, int c) {
    if (tablero[f][c] && tablero[f][c]->getTipo() == TipoEntidad::ZOMBIE) {
         zombiesMuertos++;
    }
    delete tablero[f][c];
    tablero[f][c] = nullptr;
}

void Juego::hacerDano(int f, int c, int d) {
    Entidad* e = tablero[f][c];
    if (!e) return;
    e->recibirDano(d);
    if (!e->estaViva()) { eliminarEntidad(f, c); }
}

void Juego::hacerDanoCasa(int d) {
    casaHP -= d;
    if (casaHP < 0) casaHP = 0;
}

void Juego::explosion3x3(int x, int y, int d) {
    for (int f = y - 1; f <= y + 1; f++) {
        for (int c = x - 1; c <= x + 1; c++) {
            if (f < 0 || f >= FILAS || c < 0 || c >= COLS) continue;
            Entidad* e = tablero[f][c];
            if (e && e->getTipo() == TipoEntidad::ZOMBIE)
                hacerDano(f, c, d);
        }
    }
}

bool Juego::hayZombies() const {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLS; c++) {
            if (tablero[f][c] && tablero[f][c]->getTipo() == TipoEntidad::ZOMBIE) {
                return true;
            }
        }
    }
    return false;
}

void Juego::spawnTurno() {

    int fila = rand() % FILAS;
    int colSpawn = COLS ;

    if (tablero[fila][colSpawn] != nullptr) return;

    Entidad* z = nullptr;
    int tipo = rand() % 4;

    if (tipo == 0) z = new ZombieNormal(colSpawn, fila);
    else if (tipo == 1) z = new ZombieCono(colSpawn, fila);
    else if (tipo == 2) z = new ZombieBalde(colSpawn, fila);
    else if (tipo == 3) z = new ZombieFutbol(colSpawn, fila);

    if (z)
        colocarEntidad(z, fila, colSpawn);
}

void Juego::imprimirTablero() const {

    cout << "\n      H";
    for (int i = 1; i < COLS; i++)
        cout << "     " << i+1;
    cout << "\n   +----------------------------------------------------------------+\n";

    for (int f = 0; f < FILAS; f++) {
        cout << " " << f + 1 << " | H | ";

        for (int c = 1; c < COLS; c++) {
cncjhsmd
            if (tablero[f][c] == nullptr)
                cout << "    | ";
            else {
                string sp = tablero[f][c]->getSprite();
                while (sp.length() < 4) sp += " ";
                cout << sp << " | ";
            }
        }
        cout << "\n   +----------------------------------------------------------------+\n";
    }
}

void Juego::faseColocacion() {
    while (true) {

        imprimirTablero();

        cout << "\nSoles: " << soles;
        cout << "\n1. Colocar planta";
        cout << "\n2. Quitar planta";
        cout << "\n3. Empezar oleada";
        cout << "\nOpcion: ";

        int op;
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        if (op == 3) return;

        if (op == 1) {
            pair <int,int> casilla;
            cout << "Ingrese las coordenadas en formato (a b):";
            cin >> casilla;
            int f = casilla.first;
            int c = casilla.second;
            f--; c--;

            if (f < 0 || f >= FILAS || c < 1 || c >= COLS - 1) {
                cout << "Posicion invalida (Fila 1 hasta el 5, Columna 2 hasta el 9).\n";
                continue;
            }

            if (tablero[f][c]) {
                cout << "Ya hay algo alli.\n";
                continue;
            }

            cout << "\nPlanta:"
                 << "\n1. Girasol (50)"
                 << "\n2. Lanzaguisantes (100)"
                 << "\n3. Repetidora (200)"
                 << "\n4. Nuez (75)"
                 << "\n5. Papapum (25)"
                 << "\n6. Petacereza (150)"
                 << "\nEleccion: ";

            int p; if (!(cin >> p)) continue;
            Entidad* nueva = nullptr;
            int costo = 0;

            if (p == 1) { nueva = new Girasol(c, f); costo = 50; }
            else if (p == 2) { nueva = new Lanzaguisantes(c, f); costo = 100; }
            else if (p == 3) { nueva = new Repetidora(c, f); costo = 200; }
            else if (p == 4) { nueva = new Nuez(c, f); costo = 75; }
            else if (p == 5) { nueva = new Papapum(c, f); costo = 25; }
            else if (p == 6) { nueva = new Petacereza(c, f); costo = 150; }

            if (!nueva) {
                cout << "Planta no valida.\n";
                continue;
            }

            if (soles < costo) {
                cout << "No tienes suficientes soles.\n";
                delete nueva;
                continue;
            }

            soles -= costo;
            colocarEntidad(nueva, f, c);
        }

        if (op == 2) {
            int f, c;
            cout << "Fila: "; if (!(cin >> f)) continue;
            cout << "Col: "; if (!(cin >> c)) continue;
            f--; c--;
            if (f >= 0 && f < FILAS && c >= 1 && c < COLS - 1 && tablero[f][c] && tablero[f][c]->getTipo() == TipoEntidad::PLANTA) {
                 eliminarEntidad(f, c);
            } else {
                 cout << "No hay planta para quitar en esa posición valida.\n";
            }
        }
    }
}

void Juego::ejecutarTurno(bool spawnear) {

    turno++;
    soles += 25;
    solesGanados += 25;

    if (spawnear) {
        spawnTurno();
    }
    for (int f = 0; f < FILAS; f++) {
        for (int c = COLS - 1; c >= 0; c--) {
            if (tablero[f][c] && tablero[f][c]->estaViva() ) {
                tablero[f][c]->setprocesar(true);
            }
        }
    }
    // Proceso de entidades (derecha a izquierda)
    for (int f = 0; f < FILAS; f++) {
        for (int c = COLS - 1; c >= 0; c--) {
            if (tablero[f][c] && tablero[f][c]->estaViva() && tablero[f][c]->getprocesar()) {
                tablero[f][c]->setprocesar(false);
                tablero[f][c]->operator>>(*this);
            }
        }
    }

    imprimirTablero();

    cout << "\nTurno " << turno
         << " | Casa: " << casaHP
         << " | Soles: " << soles
         << " | Zombies muertos: " << zombiesMuertos
         << "\n";
    cout << "¿Quiere salir de la partida?\n";
    cout << "S. SI   ----   N. NO\n";
    char cancelar;
    cin >> cancelar;
    if (cancelar == 'S' or cancelar == 's') cancelar_partida = true;
    else cancelar_partida = false;
    cin.ignore();
    cout << "Presione ENTER...";
    cin.get();
}

void Juego::iniciar(const string& nombre, int maxOleadas) {

    jugador = nombre;

    while (oleada <= maxOleadas && casaHP > 0) {

        cout << "\n--- OLEADA " << oleada << ": FASE DE COLOCACION ---";
        faseColocacion();

        int zombisTotales = 5 + (oleada - 1) * 2;
        if (zombisTotales < 5) zombisTotales = 5;

        int cadencia = (oleada >= 7) ? 3 : 1;
        int zombisPendientes = zombisTotales;

        cout << "\n--- OLEADA " << oleada << " INICIADA (" << zombisTotales
             << " Zombis, apareceran de " << cadencia << " en " << cadencia << ") --- \n";


        while (zombisPendientes > 0 || hayZombies()) {
            if (casaHP <= 0) break;

            bool debeSpawnear = (zombisPendientes > 0);

            if (debeSpawnear) {
                int spawnsEnEsteTurno = min(cadencia, zombisPendientes);

                for(int i = 0; i < spawnsEnEsteTurno; ++i) {
                    spawnTurno();
                }
                zombisPendientes -= spawnsEnEsteTurno;
            }

            if (zombisPendientes == 0 && !hayZombies()) {
                break;
            }
            ejecutarTurno(false);
            if (cancelar_partida) {
                casaHP = 0;
                break;
            };
        }

        if (casaHP <= 0) break;

        cout << "\n==========================================" << endl;
        cout << "!!! ¡OLEADA " << oleada << " SUPERADA! !!!" << endl;
        cout << "==========================================" << endl;
        oleada++;
    }

    bool victoria = (casaHP > 0 && oleada > maxOleadas);
    if (victoria) {
        cout << "\n=============================================" << endl;
        cout << "!!! ¡FELICIDADES, HAS GANADO LA PARTIDA! !!!" << endl;
        cout << "=============================================" << endl;
    } else if (casaHP <= 0) {
        cout << "\n=============================================" << endl;
        cout << "!!! ¡FIN DEL JUEGO! Los zombies llegaron a tu casa. !!!" << endl;
        cout << "=============================================" << endl;
    }

    guardarStats(casaHP > 0);
}
void Juego::guardarStats(bool victoria) const {

    ofstream out("resultados.txt", ios::app);
    time_t ahora = time(0);
    out << ctime(&ahora);
    out << jugador
        << " | Victoria: " << (victoria ? "Sí" : "No")
        << " | Oleada: " << oleada
        << " | Zombies muertos: " << zombiesMuertos
        << " | Soles ganados: " << solesGanados
        << "\n";
    out.close();
}
