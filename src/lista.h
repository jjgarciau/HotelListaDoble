#ifndef HOTEL_LISTA_H
#define HOTEL_LISTA_H

#include <string>
#include <vector>
#include <iosfwd>
#include "Nodo.h"

using namespace std;

class Lista {
private:
    Nodo* head{nullptr};       // cabeza por orden de llegada
    Nodo* tail{nullptr};       // cola por orden de llegada
    Nodo* headAlpha{nullptr};  // cabeza por orden alfabético
    Nodo* tailAlpha{nullptr};  // cola por orden alfabético
    size_t n{0};

    string archivo; // ruta a hotel.txt


    static string trim(const string &s);
    static string toLower(const string &s);
    static int ciCompare(const string &a, const string &b);

    bool habitacionOcupada(int h) const;
    Nodo* buscarNodoPorHabitacion(int h) const;
    vector<Nodo*> buscarNodosPorNombre(const string &nombre) const;

    void enlazarLlegadaAlFinal(Nodo* nodo);
    void insertarEnOrdenAlfabetico(Nodo* nodo);

    void limpiar(); // libera memoria

public:
    explicit Lista(string archivoHotelTxt);
    ~Lista();

    Lista(const Lista&) = delete;
    Lista& operator=(const Lista&) = delete;

    // Carga/guardado
    bool cargarDesdeArchivo();
    bool guardarEnArchivo() const;


    bool insertarHuesped(const string &nombre, int habitacion, bool silencioso=false);

    // Búsquedas
    vector<int> buscarHabitacionesPorNombre(const string &nombre) const;
    string buscarNombrePorHabitacion(int habitacion) const;

    // Listados
    void mostrarAlfabetico(ostream &os) const;
    void mostrarLlegada(ostream &os) const;

    // Vecinos (habitaciones consecutivas)
    void consultarVecinos(int habitacion, ostream &os) const;


    int sugerirHabitacionCercana(int solicitada) const;

    size_t tam() const { return n; }
};

#endif // HOTEL_LISTA_H
