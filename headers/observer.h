#ifndef OBSERVER_H_INCLUDED
#define OBSERVER_H_INCLUDED

#include "estructurasDeDatos.h"

class Observer
{
public:
    virtual void receive(std::string message) = 0;
};

class Subject
{
public:
    void update(std::string message);
    void addObserver(Observer* observer);
private:
    Lista<Observer*> views;
};


#endif