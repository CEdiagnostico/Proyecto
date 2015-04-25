//
// Created by roberto on 25/04/15.
//

#include "../Headers/Updater.h"

void Updater::actualizarObjetos(Member* lista) {
    int actives = 0;
    srand(time(NULL));
    for (int i = 1; i < NUMBER_OF_MEMBERS-1; i++) {
        Member *tmp = static_cast<Member *>(lista + i * sizeof(Member));
        if (tmp->getFlag()) {
            if (tmp->getY() < 10) {
                tmp->setY(tmp->getY() + 1);
                actives++;
            } else {
                tmp->changeFlag();
            }
        }
    }
    while (actives < 3) {
        Member *tmp = static_cast<Member *>(lista + (rand() % 6 + 1) * sizeof(Member));
        if (!(tmp->getFlag())) {
            tmp->setY(1);
            tmp->setX(rand() % 3 + 1);
            tmp->changeFlag();
            actives++;
        }
    }
    Bala *balaJugador = static_cast<Bala *>(lista + 7 * sizeof(Member));
    if (balaJugador->getFlag()) {
        if (balaJugador->getY() > 0) {
            balaJugador->setY(balaJugador->getY() - 1);
            Member* tmp = balaJugador->colision(lista);
            if(tmp!=0 && tmp!=(Jugador*)(lista)){
                tmp->changeFlag();
            }
        }else {
            balaJugador->changeFlag();
            balaJugador->setY(10);
        }
    }
}
