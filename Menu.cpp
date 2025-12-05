#include "Menu.h"
#include "Juego.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void mostrarMenu() {

    while (true) {
        cout << "\n===== PLANTS VS ZOMBIES (ASCII) =====\n";
        cout << "1. Jugar\n2. Ver estadisticas\n3. Salir\nOpcion: ";

        int op; cin >> op;

        if (op == 1) {
            string nombre;
            cout << "Nombre: ";
            cin >> nombre;

            Juego j;
            j.iniciar(nombre, 10);
        }
        else if (op == 2) {
            fstream archivo("resultados.txt", ios::in);
            if (!archivo.is_open()) {
                cout << "No hay datos.\n";
            } else {
                string s;
                while (getline(archivo, s)) cout << s << "\n";
            }
            archivo.close();
        }
        else return;
    }
}
