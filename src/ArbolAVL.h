#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "Nodo.h"
#include "print_helpers.h" // 👈 para colores y helpers
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class ArbolAVL {
private:
  Nodo *raiz;

  // Método auxiliar para inserción
  Nodo *insertar(Nodo *nodo, Nodo *nuevoNodo) {
    if (nodo == nullptr)
      return nuevoNodo;

    if (nuevoNodo->codigoIATA < nodo->codigoIATA)
      nodo->izquierda = insertar(nodo->izquierda, nuevoNodo);
    else if (nuevoNodo->codigoIATA > nodo->codigoIATA)
      nodo->derecha = insertar(nodo->derecha, nuevoNodo);
    else {
      printError("ERROR: La sede con este código IATA ya existe.");
      return nodo;
    }

    // Actualiza altura
    nodo->altura =
        1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    // TODO: balanceo se implementará luego
    return nodo;
  }

  // Métodos auxiliares para obtener altura y factor de balanceo
  int obtenerAltura(Nodo *nodo) {
    if (nodo == nullptr)
      return 0;
    return nodo->altura;
  }

  int obtenerBalance(Nodo *nodo) {
    if (nodo == nullptr)
      return 0;
    return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
  }

public:
  ArbolAVL() { raiz = nullptr; }

  // Inserción pública
  void insertar(string codigo, string pais, string ciudad, string estFIFA,
                string estOficial, int cap, int anio) {
    Nodo *nuevoNodo =
        new Nodo(codigo, pais, ciudad, estFIFA, estOficial, cap, anio);
    raiz = insertar(raiz, nuevoNodo);
  }

  // Buscar
  Nodo *buscar(string codigo) { return buscar(raiz, codigo); }

private:
  Nodo *buscar(Nodo *nodo, string codigo) {
    if (nodo == nullptr || nodo->codigoIATA == codigo)
      return nodo;

    if (codigo < nodo->codigoIATA)
      return buscar(nodo->izquierda, codigo);
    else
      return buscar(nodo->derecha, codigo);
  }

public:
  // Mostrar nodo bonito
  void mostrarNodo(Nodo *nodo) {
    if (nodo == nullptr) {
      printError("Sede no encontrada.");
      return;
    }

    printTitulo("Datos de la Sede");
    cout << YELLOW << "IATA: " << RESET << nodo->codigoIATA << endl;
    cout << YELLOW << "País: " << RESET << nodo->pais << endl;
    cout << YELLOW << "Ciudad: " << RESET << nodo->ciudad << endl;
    cout << YELLOW << "Estadio FIFA: " << RESET << nodo->estadioFIFA << endl;
    cout << YELLOW << "Estadio Oficial: " << RESET << nodo->estadioOficial
         << endl;
    cout << YELLOW << "Capacidad: " << RESET << nodo->capacidad << endl;
    cout << YELLOW << "Año: " << RESET << nodo->anio << endl;
    cout << "---------------------------" << endl;
  }

  // Eliminar nodo (base)
  void eliminar(string codigo) { raiz = eliminar(raiz, codigo); }

private:
  Nodo *eliminar(Nodo *nodo, string codigo) {
    if (nodo == nullptr) {
      printError("Sede no encontrada para eliminar.");
      return nodo;
    }

    if (codigo < nodo->codigoIATA) {
      nodo->izquierda = eliminar(nodo->izquierda, codigo);
    } else if (codigo > nodo->codigoIATA) {
      nodo->derecha = eliminar(nodo->derecha, codigo);
    } else {
      // Caso 1: sin hijos o un hijo
      if (nodo->izquierda == nullptr) {
        Nodo *temp = nodo->derecha;
        delete nodo;
        return temp;
      } else if (nodo->derecha == nullptr) {
        Nodo *temp = nodo->izquierda;
        delete nodo;
        return temp;
      }

      // Caso 2: dos hijos → sucesor in-order
      Nodo *sucesor = nodo->derecha;
      while (sucesor->izquierda != nullptr)
        sucesor = sucesor->izquierda;

      nodo->codigoIATA = sucesor->codigoIATA;
      nodo->pais = sucesor->pais;
      nodo->ciudad = sucesor->ciudad;
      nodo->estadioFIFA = sucesor->estadioFIFA;
      nodo->estadioOficial = sucesor->estadioOficial;
      nodo->capacidad = sucesor->capacidad;
      nodo->anio = sucesor->anio;

      nodo->derecha = eliminar(nodo->derecha, sucesor->codigoIATA);
    }

    // Actualiza altura (balanceo lo hace Dev2)
    nodo->altura =
        1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
    return nodo;
  }

public:
  // Guardar CSV
  void guardarEnCSV(ofstream &archivo) { guardarEnCSV(raiz, archivo); }

private:
  void guardarEnCSV(Nodo *nodo, ofstream &archivo) {
    if (nodo != nullptr) {
      guardarEnCSV(nodo->izquierda, archivo);

      archivo << nodo->codigoIATA << "," << nodo->pais << "," << nodo->ciudad
              << "," << nodo->estadioFIFA << "," << nodo->estadioOficial << ","
              << nodo->capacidad << "," << nodo->anio << "\n";

      guardarEnCSV(nodo->derecha, archivo);
    }
  }

public:
  // In-Order
  void inOrder() { inOrder(raiz); }

  void inOrder(Nodo *nodo) {
    if (nodo != nullptr) {
      inOrder(nodo->izquierda);
      mostrarNodo(nodo);
      inOrder(nodo->derecha);
    }
  }
};

#endif
