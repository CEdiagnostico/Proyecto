//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_JUGADOR_H
#define PROYECTO_JUGADOR_H

#include "Member.h"

class Jugador: public Member{
    int combustible;
    public:
        Jugador(int, int, int);
        bool colisiones(Member*);
        void bajarCombustible();
        int getCombustible();
};


#endif //PROYECTO_JUGADOR_H
