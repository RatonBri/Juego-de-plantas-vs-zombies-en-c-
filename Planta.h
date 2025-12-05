#ifndef PLANTA_H
#define PLANTA_H

#include "Entidad.h"

class Planta : public Entidad {

protected:
    int costo;

public:
    Planta(int col, int fil, int hp, int c)
        : Entidad(col, fil, hp, TipoEntidad::PLANTA), costo(c) {}

    int getCosto() const { return costo; }
    // Planta usa el recibirDano por defecto de Entidad
};

class Girasol : public Planta {
public:
    Girasol(int col, int fil);
    void operator>>(class Juego& juego) override;

    //void operator->(class Juego& juego)
};

class Lanzaguisantes : public Planta {
public:
    Lanzaguisantes(int col, int fil);
    void operator>>(class Juego& juego) override;
};

class Repetidora : public Planta {
public:
    Repetidora(int col, int fil);
    void operator>>(class Juego& juego) override;
};

class Nuez : public Planta {
public:
    Nuez(int col, int fil);
    void operator>>(class Juego& juego) override { /* La Nuez solo espera */ }
};

class Papapum : public Planta {
    int armado;
public:
    Papapum(int col, int fil);
    void operator>>(class Juego& juego) override;
};

class Petacereza : public Planta {
public:
    Petacereza(int col, int fil);
    void operator>>(class Juego& juego) override;
};

#endif