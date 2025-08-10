#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
public:
  string codigoIATA;

  string pais;
  string ciudad;
  string estadioFIFA;
  string estadioOficial;
  int capacidad;
  int anio;

  Nodo *izquierda;
  Nodo *derecha;

  int altura;

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
    altura = 1;
  }
};

#endif
