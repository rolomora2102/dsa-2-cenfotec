#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
public:
  // Clave de búsqueda
  string codigoIATA;

  // Datos de la sede
  string pais;
  string ciudad;
  string estadioFIFA;
  string estadioOficial;
  int capacidad;
  int anio;

  // Punteros del árbol
  Nodo *izquierda;
  Nodo *derecha;

  // Factor de altura para balanceo (AVL)
  int altura;

  // Constructor
  Nodo(string codigo, string p, string c, string estFIFA, string estOficial,
       int cap, int a) {
    codigoIATA = codigo;
    pais = p;
    ciudad = c;
    estadioFIFA = estFIFA;
    estadioOficial = estOficial;
    capacidad = cap;
    anio = a;

    izquierda = nullptr;
    derecha = nullptr;
    altura = 1; // Por default, un nodo nuevo tiene altura 1
  }
};

#endif
