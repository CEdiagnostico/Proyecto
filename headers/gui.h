
#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include"objects.h"
#include"estructurasDeDatos.h"
#include"constants.h"
#include "observer.h"



class Gui: public Observer {
    public:
    virtual void receive(std::string message);

    int start();
        void addLevel(Floor &floor);
        void addPlayer(int id);
        void addEnemy(int id);
        void addBullet(int id);
        void addBonus(int id);
        void updatePlayer(int id, int x, int y);
        void initPlane(Plane &plane);
        void drawPlane(Plane &plane);
        void drawEnemy(Enemy &enemy);
        void drawBullet(Bullet &bullet);
        void drawTerrain();
    private:
        Lista<Floor> mundo;
        ALLEGRO_BITMAP *player;
};


#endif // GUI_H_INCLUDED
