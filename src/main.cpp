#include "ArbolAVL.h"
#include "CSVManager.h"
#include "Nodo.h"
#include "print_helpers.h"
#include <iostream>
#include <limits.h>
#include <unistd.h>

using namespace std;

void printMenu() {
  printTitulo("MENÚ SEDES");
  cout << CYAN << "1. Insertar nueva sede" << RESET << endl;
  cout << CYAN << "2. Buscar sede" << RESET << endl;
  cout << CYAN << "3. Modificar sede" << RESET << endl;
  cout << CYAN << "4. Eliminar sede" << RESET << endl;
  cout << CYAN << "5. Listar sedes (In-Order)" << RESET << endl;
  cout << CYAN << "0. Guardar y Salir" << RESET << endl;
  cout << MAGENTA << "Seleccione una opción: " << RESET;
}

int main() {
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  cout << BOLD << GREEN << "CWD: " << cwd << RESET << endl;

  ArbolAVL arbol;

  // Carga inicial
  CSVManager::cargarCSV(arbol, "../data/sedes.csv");
  printOK("Sedes cargadas desde CSV.");

  int opcion;
  do {
    printMenu();
    cin >> opcion;

    switch (opcion) {
    case 1: {
      string iata, pais, ciudad, estFIFA, estOficial;
      int capacidad, anio;

      cout << CYAN << "Código IATA: " << RESET;
      cin >> iata;
      cout << CYAN << "País: " << RESET;
      cin.ignore();
      getline(cin, pais);
      cout << CYAN << "Ciudad: " << RESET;
      getline(cin, ciudad);
      cout << CYAN << "Estadio FIFA: " << RESET;
      getline(cin, estFIFA);
      cout << CYAN << "Estadio Oficial: " << RESET;
      getline(cin, estOficial);
      cout << CYAN << "Capacidad: " << RESET;
      cin >> capacidad;
      cout << CYAN << "Año de inauguración: " << RESET;
      cin >> anio;

      arbol.insertar(iata, pais, ciudad, estFIFA, estOficial, capacidad, anio);
      printOK("Sede insertada correctamente.");
      break;
    }

    case 2: {
      string codigo;
      cout << CYAN << "Ingrese código IATA a buscar: " << RESET;
      cin >> codigo;

      Nodo *resultado = arbol.buscar(codigo);
      arbol.mostrarNodo(resultado);
      break;
    }

    case 3: {
      string codigo;
      cout << CYAN << "Ingrese código IATA a modificar: " << RESET;
      cin >> codigo;

      Nodo *resultado = arbol.buscar(codigo);
      if (resultado == nullptr) {
        printError("Sede no encontrada.");
        break;
      }

      arbol.mostrarNodo(resultado);

      cout << CYAN << "Nuevo País: " << RESET;
      cin.ignore();
      getline(cin, resultado->pais);
      cout << CYAN << "Nueva Ciudad: " << RESET;
      getline(cin, resultado->ciudad);
      cout << CYAN << "Nuevo Estadio FIFA: " << RESET;
      getline(cin, resultado->estadioFIFA);
      cout << CYAN << "Nuevo Estadio Oficial: " << RESET;
      getline(cin, resultado->estadioOficial);
      cout << CYAN << "Nueva Capacidad: " << RESET;
      cin >> resultado->capacidad;
      cout << CYAN << "Nuevo Año de inauguración: " << RESET;
      cin >> resultado->anio;

      printOK("Sede modificada correctamente.");
      break;
    }

    case 4: {
      string codigo;
      cout << CYAN << "Ingrese código IATA a eliminar: " << RESET;
      cin >> codigo;

      arbol.eliminar(codigo); // Recuerda implementar esto en ArbolAVL
      printOK("Proceso de eliminación completado (verifica mensaje interno).");
      break;
    }

    case 5:
      printTitulo("Listado de sedes (In-Order)");
      arbol.inOrder();
      break;

    case 0:
      printOK("Guardando cambios...");
      CSVManager::guardarCSV(arbol, "../data/sedes.csv");
      printOK("Archivo guardado. ¡Hasta luego!");
      break;

    default:
      printError("Opción inválida. Intente de nuevo.");
    }

  } while (opcion != 0);

  return 0;
}
