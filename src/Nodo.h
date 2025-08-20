#ifndef HOTEL_NODO_H
#define HOTEL_NODO_H

#include <string>

class Nodo {
public:
    std::string nombre;
    int habitacion;


    Nodo* prev;
    Nodo* next;


    Nodo* prevAlpha;
    Nodo* nextAlpha;

    explicit Nodo(std::string nombre, int habitacion);
};

#endif // HOTEL_NODO_H
