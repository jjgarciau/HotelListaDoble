#include "Nodo.h"
#include <utility>
using namespace std;

Nodo::Nodo(string n, int h)
    : nombre(move(n)),
      habitacion(h),
      prev(nullptr),
      next(nullptr),
      prevAlpha(nullptr),
      nextAlpha(nullptr) {}
