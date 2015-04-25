//
// Created by roberto on 24/04/15.
//

#include "Enemigo.h"

Enemigo(int paramId, int paramX, int paramY){
    super(0,paramId,paramX,paramY);
};

~Enemigo(){
    ~Member();
};