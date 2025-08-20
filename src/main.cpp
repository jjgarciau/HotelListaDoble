#include "lista.h"
#include <iostream>
#include <string>
using namespace std;

static int leerEntero(const string &prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) return 0;
        try {
            size_t pos = 0;
            int v = stoi(s, &pos);
            if (pos != s.size()) throw runtime_error("extra");
            return v;
        } catch (...) {
            cout << "Ingrese un numero valido.\n";
        }
    }
}

static string leerLinea(const string &prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

static void menu() {
    cout << "\n===== Sistema de Huespedes (Lista Doble) =====\n";
    cout << "1) Ingresar nuevo huesped\n";
    cout << "2) Buscar por nombre\n";
    cout << "3) Buscar por numero de habitacion\n";
    cout << "4) Mostrar lista alfabetica\n";
    cout << "5) Mostrar lista por orden de llegada\n";
    cout << "6) Consultar vecinos por habitacion\n";
    cout << "7) Guardar y salir\n";
}

int main() {
    Lista lista("../hotel.txt");

    while (true) {
        menu();
        if (const int op = leerEntero("Elija una opcion:  "); op == 1) {
            string nombre = leerLinea("Nombre del huesped: ");

            if (const int hab = leerEntero("Numero de habitacion deseado: "); !lista.insertarHuesped(nombre, hab, /*silencioso=*/true)) {
                // Ocupada -> sugerir
                int sugerida = lista.sugerirHabitacionCercana(hab);
                if (sugerida == hab) {

                    cout << "La habitacion " << hab << " esta ocupada.\n";
                } else {
                    cout << "La habitacion " << hab << " esta ocupada.\n";
                    cout << "Sugerencia: habitacion " << sugerida << ". ¿Acepta? (S/N): ";
                    string resp;
                    getline(cin, resp);
                    if (!resp.empty() && (resp[0]=='s' || resp[0]=='S')) {
                        if (lista.insertarHuesped(nombre, sugerida, /*silencioso=*/false)) {
                            cout << "Huesped insertado en habitacion " << sugerida << ".\n";
                        } else {
                            cout << "No fue posible insertar.\n";
                        }
                    } else {

                        int nuevo = leerEntero("Ingrese un numero de habitacion disponible: ");
                        if (lista.insertarHuesped(nombre, nuevo, /*silencioso=*/false)) {
                            cout << "Huesped insertado en habitacion " << nuevo << ".\n";
                        } else {
                            cout << "La habitacion " << nuevo << " tambien esta ocupada. Operacion cancelada.\n";
                        }
                    }
                }
            } else {

                lista.guardarEnArchivo();
                cout << "Huesped insertado en habitacion " << hab << ".\n";
            }

        } else if (op == 2) {
            string nombre = leerLinea("Nombre a buscar: ");
            auto habs = lista.buscarHabitacionesPorNombre(nombre);
            if (habs.empty()) {
                cout << "Ese huesped no fue encontrado. (that guest was not found.)\n";
            } else {
                cout << "Habitaciones de \"" << nombre << "\": ";
                for (size_t i=0;i<habs.size();++i) {
                    cout << habs[i] << (i+1<habs.size()? ", ":"\n");
                }
            }

        } else if (op == 3) {
            int hab = leerEntero("Numero de habitacion a buscar: ");
            auto nombre = lista.buscarNombrePorHabitacion(hab);
            if (nombre.empty()) {
                cout << "Ese huesped no fue encontrado. (that guest was not found.)\n";
            } else {
                cout << "Habitacion " << hab << " esta ocupada por: " << nombre << "\n";
            }

        } else if (op == 4) {
            lista.mostrarAlfabetico(cout);

        } else if (op == 5) {
            lista.mostrarLlegada(cout);

        } else if (op == 6) {
            int hab = leerEntero("Numero de habitacion para consultar vecinos: ");
            lista.consultarVecinos(hab, cout);

        } else if (op == 7) {
            if (lista.guardarEnArchivo()) {
                cout << "Datos guardados en hotel.txt. ¡Hasta luego!\n";
            } else {
                cout << "No se pudo guardar el archivo.\n";
            }
            break;
        } else {
            cout << "Opcion no valida.\n";
        }
    }
    return 0;
}
