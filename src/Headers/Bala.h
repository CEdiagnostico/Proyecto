//
// Created by roberto on 25/04/15.
//

#ifndef PROYECTO_BALA_H
#define PROYECTO_BALA_H

#include "Member.h"

class Bala: public Member{
    public:
        Bala(int,int,int);
        Member* colision(Member*);
};


#endif //PROYECTO_BALA_H
