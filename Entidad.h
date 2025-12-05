#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <string>
#include <vector>

enum class TipoEntidad {
    PLANTA,
    ZOMBIE
};

class Entidad {

protected:
    int x, y;       // columna, fila
    int vida;
    bool viva;
    bool procesar = true;

    TipoEntidad tipo;
    std::vector<std::string> sprites;
    int spriteIndex;

public:

    Entidad(int cx, int cy, int hp, TipoEntidad t)
        : x(cx), y(cy), vida(hp), viva(true), tipo(t), spriteIndex(0) {}

    virtual ~Entidad() {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool getprocesar() const {
        return procesar;
    }
    void setprocesar(bool flag) {
        procesar = flag;
    }

    int getVida() const { return vida; }

    virtual void recibirDano(int d) {
        vida -= d;
        if (vida <= 0) viva = false;
    }

    void setVida(int v) { vida = v; if (vida <= 0) viva = false; }

    bool estaViva() const { return viva; }

    TipoEntidad getTipo() const { return tipo; }

    void setPos(int cx, int cy) { x = cx; y = cy; }

    void setSprites(const std::vector<std::string>& s) {
        sprites = s;
    }

    std::string getSprite() const {
        if (sprites.empty()) return "?";
        return sprites[spriteIndex];
    }

    void setSpriteIndex(int i) {
        if (i >= 0 && i < (int)sprites.size()) spriteIndex = i;
    }

    virtual void operator>>(class Juego& juego) = 0;
};

#endif