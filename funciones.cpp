

#include "funciones.h"

istream& operator>>(istream& in, pair<int,int>& p) {
    char p1, p2;
    in >> p1 >> p.first >> p.second >> p2;
    return in;
}