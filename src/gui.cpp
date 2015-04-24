#include"../headers/gui.h"
#include "protohandler.h"


using namespace std;

ALLEGRO_COLOR WHITE = al_map_rgb(255,255,255);
ALLEGRO_COLOR GREEN_GRASS = al_map_rgb(0,92,9);
ALLEGRO_COLOR BLUE_WATER = al_map_rgb(64, 164, 223);

int Gui::start()
{
    //variables primitivas
    bool done = false; // make it better

    //variables de objeto
	//Lista<Plane> jugadores;
	Lista<Plane>* jugadores = new Lista<Plane>();
	Lista<Enemy>* enemigos = new Lista<Enemy>();
	Lista<Bonus>* bonus = new Lista<Bonus>();
	Lista<int> balas;

    //variables de Allegro
    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_BITMAP *player;

    //Inicializacion
    if(!al_init())
        return -1;

    display = al_create_display(WIDTH, HEIGHT);

    if (!display)
        return -1;

    al_init_primitives_addon();
    al_init_image_addon();
    Plane plane;
    Enemy enemy;
    enemy.x =100;
    enemy.y = 200;
    Bullet bullet;
    bullet.x = 200;
    bullet.y = 300;
    initPlane(plane);
    jugadores->insertarAlFinal(plane);



    while(!done)
    {
    drawTerrain();
        for(int i =0;i<jugadores->len();i++)
        {
            Plane plane = jugadores->datoPosicion(i);
            drawPlane(plane);
        }
        for(int i =0;i<enemigos->len();i++)
        {
            Enemy enemy = enemigos->datoPosicion(i);
            drawEnemy(enemy);
        }


        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }





    return 0;
}

void Gui::addLevel(Floor &floor)
{
    int largo = HEIGHT/PIXEL;
    Lista<Floor>* pisos= &mundo;
    pisos->insertarAlInicio(floor);
    if (pisos->len()>largo)
    {
        pisos->borrarPos(largo-1);
    }
}

void Gui::initPlane(Plane &plane)
{

	plane.x = WIDTH / 2;
	plane.y = HEIGHT * 2 / 3;
	plane.ID = PLAYER;
	plane.speed = 7;
}

void Gui::drawPlane(Plane &plane)
{
    player = al_load_bitmap("player.png");
    al_draw_bitmap(player, plane.x, plane.y, 0);
}

void Gui::drawEnemy(Enemy &enemy)
{
    if (!enemy.death){
        if (enemy.isDying)
        {
            al_draw_filled_rectangle(enemy.x, enemy.y, enemy.x + 15, enemy.y - 15, al_map_rgb(255, 0, 0));
        }
        else
        {
            //al_draw_filled_rectangle(enemy.x+2, enemy.y , enemy.x + 22, enemy.y + 20, al_map_rgb(0, 255, 0));
            al_draw_filled_triangle(enemy.x, enemy.y, enemy.x + 12, enemy.y + 24, enemy.x + 24, enemy.y, al_map_rgb(0, 0, 255));


            al_draw_filled_rectangle(enemy.x + 4, enemy.y+5, enemy.x + 8, enemy.y + 8, al_map_rgb(255, 0, 0));
            al_draw_filled_rectangle(enemy.x + 16, enemy.y+5, enemy.x + 20,enemy.y + 8, al_map_rgb(255, 0, 0));
        }
	}
}


void Gui::drawBullet(Bullet &bullet)
{
    if (!bullet.death){
        al_draw_filled_circle(bullet.x,bullet.y,2.0,al_map_rgb(255,255,255));
	}
}
void Gui::drawTerrain()
{
    Lista<Floor>* lista = &mundo;
    for(int i=0;i<lista->len();i++)
    {
        Floor piso =  lista->datoPosicion(i);
        al_draw_filled_rectangle(0,i*PIXEL,piso.inicio,(i+1)*PIXEL, al_map_rgb(0,92,9));
        al_draw_filled_rectangle(piso.fin,i*PIXEL,WIDTH,(i+1)*PIXEL,al_map_rgb(0,92,9));
        if (piso.puente) al_draw_filled_rectangle(piso.inicio,i*PIXEL,piso.fin,(i+1)*PIXEL, al_map_rgb(102, 51, 0));
        else al_draw_filled_rectangle(piso.inicio,i*PIXEL,piso.fin,(i+1)*PIXEL, al_map_rgb(64, 164, 223));
    }
}

void Gui::receive(std::string message) {
    StructEvento evento = proto::readEvent(message);
}
