//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_MEMBER_H
#define PROYECTO_MEMBER_H

#include <cstdlib>

class Member {
    protected:
        int active;
        int x;
        int y;
        int id;
        int combustible;
        int vida;
    public:
        void setX(int);
        void setY(int);
        void changeFlag();
        int getX();
        int getY();
        int getId();
        int getFlag();
};


#endif //PROYECTO_MEMBER_H
