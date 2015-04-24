#include "observer.h"

void Subject::update(std::string message) {
    for (int i = 0; i < views.len(); ++i) {
        views.datoPosicion(i)->receive(message);
    }
}
void Subject::addObserver(Observer* observer) {
    views.insertarAlFinal(observer);
}