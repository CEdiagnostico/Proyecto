//
// Created by roberto on 25/04/15.
//

#include "Updater.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Updater::actualizarObjetos(Member* lista){
    int actives = 0;
    srand (time(NULL));
    for(int i = 1; i<7; i++){
        Member* tmp = static_cast<Member*>(lista+i*sizeof(Member));
        if(tmp->getFlag()){
            if(tmp->getY()<5){
                tmp->setY(tmp->getY()+1);
                actives++;
            }else{
                tmp->changeFlag();
            }
        }
    }
    while(actives<3){
        Member* tmp = static_cast<Member*>(lista + (rand()%6+1)*sizeof(Member));
        if(!(tmp->getFlag())){
            tmp->setY(1);
            tmp->setX(rand()%3+1);
            tmp->changeFlag();
            actives++;
        }
    }
}
