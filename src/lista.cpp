#include "lista.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

string Lista::trim(const string &s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace(static_cast<unsigned char>(s[i]))) ++i;
    while (j > i && isspace(static_cast<unsigned char>(s[j-1]))) --j;
    return s.substr(i, j - i);
}

string Lista::toLower(const string &s) {
    string r;
    r.reserve(s.size());
    for (unsigned char c : s) r.push_back(static_cast<char>(tolower(c)));
    return r;
}

int Lista::ciCompare(const string &a, const string &b) {
    string la = toLower(a);
    string lb = toLower(b);
    if (la < lb) return -1;
    if (la > lb) return 1;
    return 0;
}


Lista::Lista(string archivoHotelTxt) : archivo(move(archivoHotelTxt)) {
    cargarDesdeArchivo();
}

Lista::~Lista() {

    guardarEnArchivo();
    limpiar();
}

void Lista::limpiar() {
    Nodo *p = head;
    while (p) {
        Nodo *nx = p->next;
        delete p;
        p = nx;
    }
    head = tail = headAlpha = tailAlpha = nullptr;
    n = 0;
}

bool Lista::cargarDesdeArchivo() {
    ifstream in(archivo);
    if (!in.is_open()) {

        ofstream create(archivo);
        return create.is_open();
    }
    limpiar();
    string linea;
    while (true) {
        string nombre;
        string numeroStr;
        if (!getline(in, nombre)) break;
        if (!getline(in, numeroStr)) break;
        nombre = trim(nombre);
        numeroStr = trim(numeroStr);
        if (nombre.empty() || numeroStr.empty()) continue;
        int num;
        try {
            num = stoi(numeroStr);
        } catch (...) {
            continue;
        }
        insertarHuesped(nombre, num, /*silencioso=*/true);
    }
    return true;
}

bool Lista::guardarEnArchivo() const {
    ofstream out(archivo, ios::trunc);
    if (!out.is_open()) return false;
    // Guardamos en orden de llegada
    for (Nodo *p = head; p; p = p->next) {
        out << p->nombre << "\n" << p->habitacion << "\n";
    }
    return true;
}

bool Lista::habitacionOcupada(int h) const {
    return buscarNodoPorHabitacion(h) != nullptr;
}

Nodo* Lista::buscarNodoPorHabitacion(int h) const {
    for (Nodo *p = head; p; p = p->next) {
        if (p->habitacion == h) return p;
    }
    return nullptr;
}

vector<Nodo*> Lista::buscarNodosPorNombre(const string &nombre) const {
    vector<Nodo*> res;
    string target = toLower(trim(nombre));
    for (Nodo *p = head; p; p = p->next) {
        if (toLower(p->nombre) == target) res.push_back(p);
    }
    return res;
}

void Lista::enlazarLlegadaAlFinal(Nodo *nodo) {
    nodo->prev = tail;
    nodo->next = nullptr;
    if (!head) head = nodo;
    if (tail) tail->next = nodo;
    tail = nodo;
}

void Lista::insertarEnOrdenAlfabetico(Nodo *nodo) {
    if (!headAlpha) {
        headAlpha = tailAlpha = nodo;
        nodo->prevAlpha = nodo->nextAlpha = nullptr;
        return;
    }
    // Buscar posicion por nombre
    Nodo *p = headAlpha;
    while (p && ciCompare(p->nombre, nodo->nombre) <= 0) {
        p = p->nextAlpha;
    }
    if (!p) {

        nodo->prevAlpha = tailAlpha;
        nodo->nextAlpha = nullptr;
        tailAlpha->nextAlpha = nodo;
        tailAlpha = nodo;
    } else if (!p->prevAlpha) {

        nodo->prevAlpha = nullptr;
        nodo->nextAlpha = p;
        p->prevAlpha = nodo;
        headAlpha = nodo;
    } else {

        Nodo *prev = p->prevAlpha;
        nodo->prevAlpha = prev;
        nodo->nextAlpha = p;
        prev->nextAlpha = nodo;
        p->prevAlpha = nodo;
    }
}

bool Lista::insertarHuesped(const string &nombre, int habitacion, bool silencioso) {
    if (habitacionOcupada(habitacion)) {
        return false;
    }
    auto *nodo = new Nodo(nombre, habitacion);
    enlazarLlegadaAlFinal(nodo);
    insertarEnOrdenAlfabetico(nodo);
    ++n;

    if (!silencioso) {

        guardarEnArchivo();
    }
    return true;
}

vector<int> Lista::buscarHabitacionesPorNombre(const string &nombre) const {
    vector<int> habs;
    auto nodos = buscarNodosPorNombre(nombre);
    for (auto *p : nodos) habs.push_back(p->habitacion);
    return habs;
}

string Lista::buscarNombrePorHabitacion(int habitacion) const {
    if (auto *p = buscarNodoPorHabitacion(habitacion)) return p->nombre;
    return {};
}

void Lista::mostrarAlfabetico(ostream &os) const {
    os << "=== Lista de huespedes (Alfabetico) ===\n";
    for (Nodo *p = headAlpha; p; p = p->nextAlpha) {
        os << p->nombre << " - Habitacion " << p->habitacion << "\n";
    }
    if (!headAlpha) os << "(lista vacia)\n";
}

void Lista::mostrarLlegada(ostream &os) const {
    os << "=== Lista de huespedes (Orden de llegada) ===\n";
    for (Nodo *p = head; p; p = p->next) {
        os << p->nombre << " - Habitacion " << p->habitacion << "\n";
    }
    if (!head) os << "(lista vacia)\n";
}

void Lista::consultarVecinos(int habitacion, ostream &os) const {
    auto nombrePrev = buscarNombrePorHabitacion(habitacion - 1);
    auto nombreNext = buscarNombrePorHabitacion(habitacion + 1);
    os << "Vecinos de la habitacion " << habitacion << ":\n";
    os << "  Habitacion " << (habitacion - 1) << ": "
       << (nombrePrev.empty() ? "vacia / sin registro" : nombrePrev) << "\n";
    os << "  Habitacion " << (habitacion + 1) << ": "
       << (nombreNext.empty() ? "vacia / sin registro" : nombreNext) << "\n";
}

int Lista::sugerirHabitacionCercana(int solicitada) const {
    if (!habitacionOcupada(solicitada)) return solicitada;

    if (!habitacionOcupada(solicitada - 1)) return solicitada - 1;
    if (!habitacionOcupada(solicitada + 1)) return solicitada + 1;

    int d = 2;
    while (true) {
        int a = solicitada - d;
        int b = solicitada + d;
        if (!habitacionOcupada(a)) return a;
        if (!habitacionOcupada(b)) return b;
        if (d > 1000000) return solicitada + d;
        ++d;
    }
}
