#include "Zombies.h"
#include "Juego.h"
#include <vector>
#include <string>

// BASE
Zombie::Zombie(int x, int y, int vidaBase, int armadura,
               const std::vector<std::string>& sprites, int velocidad)
    : Entidad(x, y, vidaBase + armadura, TipoEntidad::ZOMBIE),
      armadura(armadura), velocidad(velocidad)
{
    setSprites(sprites);
}

void Zombie::recibirDano(int d) {
    Entidad::recibirDano(d);
}

// Movimiento y ataque
void Zombie::operator>>(class Juego& juego) {

    if (!estaViva()) return;

    int fila = y;
    int col = x;
    int next = col - 1;

    // 1. DAÑO A LA CASA: Chequea si el siguiente paso es la columna 0
    if (next == 0) {
        juego.hacerDanoCasa(1); // Daña la casa
        juego.hacerDano(y,x,999);       // Se autodestruye
        return;
    }

    // 2. Chequea si hay Planta enfrente (col - 1)
    Entidad* frente = juego.getEntidad(fila, next);

    if (frente && frente->getTipo() == TipoEntidad::PLANTA) {
        juego.hacerDano(fila,next,10);
        return; // Se detiene y ataca
    }

    // 3. Avanza
    else if (!frente) {
        juego.moverEntidad(fila, col, fila, next);
        col = next; // Actualiza posición para el siguiente paso (Zombie Futbol)
    }

    // 4. Se detiene si hay otro Zombi enfrente
    else if (frente && frente->getTipo() == TipoEntidad::ZOMBIE) {
        return;
    }

    actualizarSprite();
}

/* ==============================
   ZOMBIES ESPECIFICOS (Mantener como están)
   ============================== */

ZombieNormal::ZombieNormal(int x, int y)
    : Zombie(x, y, 60, 0, {"(Z)", "(z)"}, 1) {}
void ZombieNormal::actualizarSprite() {
    setSpriteIndex( (vida > 30) ? 0 : 1 );
}

ZombieCono::ZombieCono(int x, int y)
    : Zombie(x, y, 60, 20,
             {"^Z^", " Z^", " Z "}, 1)
{}

void ZombieCono::actualizarSprite() {
    if (vida > 60) setSpriteIndex(0);
    else if (vida > 40) setSpriteIndex(1);
    else setSpriteIndex(2);
}

ZombieBalde::ZombieBalde(int x, int y)
    : Zombie(x, y, 60, 30,
             {"[Z]", " Z]", " Z "}, 1)
{}

void ZombieBalde::actualizarSprite() {
    if (vida > 70) setSpriteIndex(0);
    else if (vida > 40) setSpriteIndex(1);
    else setSpriteIndex(2);
}

ZombieFutbol::ZombieFutbol(int x, int y)
    // Velocidad 2
    : Zombie(x, y, 80, 50,
             {"{Z}", " Z "}, 2)
{}

void ZombieFutbol::actualizarSprite() {
    setSpriteIndex( (vida > 80) ? 0 : 1 );
}