# HotelListaDoble

Proyecto de práctica: **Listas doblemente enlazadas** en C++.

Implementa una lista doblemente enlazada para gestionar huéspedes de un hotel,
cargando y guardando los datos en `hotel.txt` con el siguiente formato:

```
Juan Alejandro Vasquez
Juan Jose Garcia

```

## Funcionalidades

- Carga automática desde `hotel.txt` al iniciar.
- Insertar nuevo huésped (si la habitación está ocupada, sugiere la anterior o la siguiente; si ambas están ocupadas, sugiere la más cercana disponible).
- Buscar por **nombre** (muestra todas las habitaciones) o por **número de habitación** (muestra el nombre).
- Mostrar lista en **orden alfabético**.
- Mostrar lista en **orden de llegada**.
- Consultar **vecinos**: dado un número de habitación, muestra los nombres en la habitación anterior y posterior (si existen).
- Guardado en `hotel.txt` (en orden de llegada).

## Archivos principales

- `src/lista.h` y `src/lista.cpp`: implementación de la lista y los nodos.
- `src/main.cpp`: interfaz de texto (menú).
- `hotel.txt`: datos persistentes.

## Compilador y entorno
- C++17
- CMake 3.16+
- CLion 2025.1.4


## Ejecución
Abra el proyecto en CLion y ejecute **HotelListaDoble**. El programa crea `hotel.txt` si no existe.

## Link videos

- https://eafit-my.sharepoint.com/:v:/g/personal/javasquezt_eafit_edu_co/EclYF_kB5RlAnWpJk4sI8CQBAnm_Ji4S52loPctxDYaxcw?e=WrK98y&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D
- https://youtu.be/roDGn7Qzjuo