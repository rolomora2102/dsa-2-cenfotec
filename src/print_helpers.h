#ifndef PRINT_HELPERS_H
#define PRINT_HELPERS_H
#include "Nodo.h"
#include <iostream>
using namespace std;

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

inline void printTitulo(const string &titulo) {
  cout << CYAN << BOLD << "\n===== " << titulo << " =====" << RESET << endl;
}

inline void printError(const string &mensaje) {
  cout << RED << BOLD << mensaje << RESET << endl;
}

inline void printOK(const string &mensaje) {
  cout << GREEN << BOLD << mensaje << RESET << endl;
}

void mostrarNodo(Nodo *nodo) {
  if (nodo == nullptr)
    return;

  cout << YELLOW << BOLD << "Código IATA: " << RESET << nodo->codigoIATA
       << endl;
  cout << BLUE << "País: " << RESET << nodo->pais << " | "
       << "Ciudad: " << nodo->ciudad << " | "
       << "Estadio FIFA: " << nodo->estadioFIFA << " | "
       << "Estadio Oficial: " << nodo->estadioOficial << endl;
  cout << MAGENTA << "Capacidad: " << RESET << nodo->capacidad << " | " << CYAN
       << "Año inauguración: " << RESET << nodo->anio << endl;
  cout << "-------------------------------------------" << endl;
}

#endif
