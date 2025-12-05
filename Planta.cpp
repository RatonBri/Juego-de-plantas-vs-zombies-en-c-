#include "Planta.h"
#include "Juego.h"

// Girasol
Girasol::Girasol(int col, int fil)
    : Planta(col, fil, 5, 50)
{
    setSprites({ "\\|/", " | ", "/ \\" });
}

void Girasol::operator>>(class Juego& juego) {
    juego.addSoles(25);
}

// Lanzaguisantes
Lanzaguisantes::Lanzaguisantes(int col, int fil)
    : Planta(col, fil, 10, 100)
{
    setSprites({ "(\"O", "(\"O", "(\"O" });
}

void Lanzaguisantes::operator>>(class Juego& juego) {

    int fila = y;
    int col = x;

    for (int c = col + 1; c < COLS; c++) {
        Entidad* e = juego.getEntidad(fila, c);
        if (e && e->getTipo() == TipoEntidad::ZOMBIE) {
            juego.hacerDano(fila, c, 10);
            return;
        }
    }
}

// Repetidora
Repetidora::Repetidora(int col, int fil)
    : Planta(col, fil, 10, 200)
{
    setSprites({ "(\"O", "(\"O", "(\"O" });
}

void Repetidora::operator>>(class Juego& juego) {

    int fila = y;
    int col = x;

    for (int shot = 0; shot < 2; shot++) {
        for (int c = col + 1; c < COLS; c++) {
            Entidad* e = juego.getEntidad(fila, c);
            if (e && e->getTipo() == TipoEntidad::ZOMBIE) {
                juego.hacerDano(fila, c, 15);
                break;
            }
        }
    }
}

// Nuez
Nuez::Nuez(int col, int fil)
    : Planta(col, fil, 30, 75)
{
    setSprites({ "{'u'}" });
}
// Nuez::proceso está vacío en el .h

// Papapum
Papapum::Papapum(int col, int fil)
    : Planta(col, fil, 5, 25), armado(1)
{
    setSprites({ ".o.", "(\")", "PUM" });
}

void Papapum::operator>>(class Juego& juego) {
    if (armado > 0) { armado--; return; }

    // Chequea si hay un zombi justo enfrente (col - 1)
    Entidad* e_zombi = juego.getEntidad(y, x + 1);

    if (e_zombi && e_zombi->getTipo() == TipoEntidad::ZOMBIE) {
        juego.hacerDano(y, x + 1, 9999);
        juego.hacerDano(y, x, 9999);
    }
}

// Petacereza
Petacereza::Petacereza(int col, int fil)
    : Planta(col, fil, 5, 150)
{
    setSprites({ "@%@" });
}

void Petacereza:: operator>>(class Juego& juego) {
    Entidad* e_zombi = juego.getEntidad(y, x+1);
    if (e_zombi && e_zombi->getTipo() == TipoEntidad::ZOMBIE) {
        juego.explosion3x3(x, y, 90);
        juego.hacerDano(y,x,9999); // Se autodestruye
    }
}