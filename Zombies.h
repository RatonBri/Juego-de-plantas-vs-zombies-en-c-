#ifndef ZOMBIES_H
#define ZOMBIES_H

#include "Entidad.h"
#include <vector>
#include <string>

class Zombie : public Entidad {
protected:
    int armadura;
    int velocidad; // Añadido
public:
    Zombie(int x, int y, int vidaBase, int armadura,
           const std::vector<std::string>& sprites, int velocidad = 1);

    // Recibe daño y es virtualmente igual a Entidad::recibirDano
    void recibirDano(int d) override;

    void operator>>(class Juego& juego) override;
    virtual void actualizarSprite() = 0;
};

class ZombieNormal : public Zombie {
public:
    ZombieNormal(int x, int y);
    void actualizarSprite() override;
};

class ZombieCono : public Zombie {
public:
    ZombieCono(int x, int y);
    void actualizarSprite() override;
};

class ZombieBalde : public Zombie {
public:
    ZombieBalde(int x, int y);
    void actualizarSprite() override;
};

class ZombieFutbol : public Zombie {
public:
    ZombieFutbol(int x, int y);
    void actualizarSprite() override;
};

#endif