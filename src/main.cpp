#include "ArbolAVL.h"
#include "CSVManager.h"
#include "Grafo.h"
#include "Nodo.h"
#include "print_helpers.h"
#include <iostream>
#include <limits.h>
#include <unistd.h>

using namespace std;

void printMenuPrincipal()
{
  printTitulo("SISTEMA MUNDIAL FIFA 2026");
  cout << CYAN << "1. Gestión de Sedes (Árbol AVL)" << RESET << endl;
  cout << CYAN << "2. Análisis de Conectividad (Grafo)" << RESET << endl;
  cout << CYAN << "0. Guardar y Salir" << RESET << endl;
  cout << MAGENTA << "Seleccione una opción: " << RESET;
}

void printMenuSedes()
{
  printTitulo("MENÚ SEDES (ÁRBOL AVL)");
  cout << CYAN << "1. Insertar nueva sede" << RESET << endl;
  cout << CYAN << "2. Buscar sede" << RESET << endl;
  cout << CYAN << "3. Modificar sede" << RESET << endl;
  cout << CYAN << "4. Eliminar sede" << RESET << endl;
  cout << CYAN << "5. Listar sedes (In-Order)" << RESET << endl;
  cout << CYAN << "6. Listar por país" << RESET << endl;
  cout << CYAN << "7. Listar por capacidad mínima" << RESET << endl;
  cout << CYAN << "8. Listar ordenado por año" << RESET << endl;
  cout << CYAN << "0. Volver al menú principal" << RESET << endl;
  cout << MAGENTA << "Seleccione una opción: " << RESET;
}

void printMenuGrafo()
{
  printTitulo("MENÚ ANÁLISIS DE CONECTIVIDAD (GRAFO)");
  cout << CYAN << "1. Mostrar todas las conexiones" << RESET << endl;
  cout << CYAN << "2. Mostrar todas las rutas desde un origen (Flow)" << RESET
       << endl;
  cout << CYAN << "3. Calcular ruta más corta entre dos ciudades (Dijkstra)"
       << RESET << endl;
  cout << CYAN << "4. Encontrar sede más lejana desde una base" << RESET
       << endl;
  cout << CYAN << "5. Árbol de Expansión Mínima (Prim)" << RESET << endl;
  cout << CYAN << "6. Mostrar información de ciudades" << RESET << endl;
  cout << CYAN << "7. Agregar nueva conexión" << RESET << endl;
  cout << CYAN << "0. Volver al menú principal" << RESET << endl;
  cout << MAGENTA << "Seleccione una opción: " << RESET;
}

void printMenuTipoConexion()
{
  printTitulo("SELECCIONE TIPO DE CONEXIÓN");
  cout << CYAN << "1. Mostrar por distancias (km)" << RESET << endl;
  cout << CYAN << "2. Mostrar por vuelos diarios" << RESET << endl;
  cout << CYAN << "0. Volver al menú anterior" << RESET << endl;
  cout << MAGENTA << "Seleccione una opción: " << RESET;
}

void menuSedes(ArbolAVL &arbol)
{
  int opcion;
  do
  {
    printMenuSedes();
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
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
    case 2:
    {
      string codigo;
      cout << CYAN << "Ingrese código IATA a buscar: " << RESET;
      cin >> codigo;
      Nodo *resultado = arbol.buscar(codigo);
      if (resultado != nullptr)
      {
        arbol.mostrarNodo(resultado);
      }
      else
      {
        printError("Sede no encontrada.");
      }
      break;
    }
    case 3:
    {
      string codigo;
      cout << CYAN << "Ingrese código IATA a modificar: " << RESET;
      cin >> codigo;
      Nodo *resultado = arbol.buscar(codigo);
      if (resultado == nullptr)
      {
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
    case 4:
    {
      string codigo;
      cout << CYAN << "Ingrese código IATA a eliminar: " << RESET;
      cin >> codigo;
      arbol.eliminar(codigo);
      printOK("Proceso de eliminación completado.");
      break;
    }
    case 5:
      printTitulo("Listado de sedes (In-Order)");
      arbol.inOrder();
      break;
    case 6:
    {
      string pais;
      cout << CYAN << "Ingrese el país: " << RESET;
      cin.ignore();
      getline(cin, pais);
      arbol.listarPorPais(pais);
      break;
    }
    case 7:
    {
      int capacidadMin;
      cout << CYAN << "Ingrese capacidad mínima: " << RESET;
      cin >> capacidadMin;
      arbol.listarPorCapacidad(capacidadMin);
      break;
    }
    case 8:
      arbol.listarOrdenadoPorAnio();
      break;
    case 0:
      printOK("Volviendo al menú principal...");
      break;
    default:
      printError("Opción inválida. Intente de nuevo.");
    }
  } while (opcion != 0);
}

void menuGrafo(Grafo &grafo)
{
  int opcion;
  do
  {
    printMenuGrafo();
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
      int opcionTipo;
      do
      {
        printMenuTipoConexion();
        cin >> opcionTipo;

        switch (opcionTipo)
        {
        case 1:
          printTitulo("Conexiones por Distancia (km)");
          grafo.mostrarGrafoPorTipo(1);
          break;
        case 2:
          printTitulo("Conexiones por Vuelos Diarios");
          grafo.mostrarGrafoPorTipo(2);
          break;
        case 0:
          printOK("Volviendo al menú anterior...");
          break;
        default:
          printError("Opción inválida. Intente de nuevo.");
        }
      } while (opcionTipo != 0);
      break;
    }
    case 2:
    {
      string origen;
      cout << CYAN << "Ingrese código IATA de origen: " << RESET;
      cin >> origen;

      int opcionTipo;
      do
      {
        printMenuTipoConexion();
        cin >> opcionTipo;

        switch (opcionTipo)
        {
        case 1:
          printTitulo("Todas las rutas (distancias) desde " + origen);
          grafo.flow(origen, 1);
          break;
        case 2:
          printTitulo("Todas las rutas (vuelos) desde " + origen);
          grafo.flow(origen, 2);
          break;
        case 0:
          printOK("Volviendo al menú anterior...");
          break;
        default:
          printError("Opción inválida. Intente de nuevo.");
        }
      } while (opcionTipo != 0);
      break;
    }
    case 3:
    {
      string origen, destino;
      cout << CYAN << "Ingrese código IATA de origen: " << RESET;
      cin >> origen;
      cout << CYAN << "Ingrese código IATA de destino: " << RESET;
      cin >> destino;

      int opcionTipo;
      do
      {
        printMenuTipoConexion();
        cin >> opcionTipo;

        switch (opcionTipo)
        {
        case 1:
          printTitulo("Ruta más corta (por distancia) entre " + origen + " y " +
                      destino);
          grafo.dijkstra(origen, destino, 1);
          break;
        case 2:
          printTitulo("Ruta óptima (por vuelos) entre " + origen + " y " +
                      destino);
          grafo.dijkstra(origen, destino, 2);
          break;
        case 0:
          printOK("Volviendo al menú anterior...");
          break;
        default:
          printError("Opción inválida. Intente de nuevo.");
        }
      } while (opcionTipo != 0);
      break;
    }
    case 4:
    {
      string base;
      cout << CYAN << "Ingrese código IATA de la sede base: " << RESET;
      cin >> base;
      grafo.encontrarSedeMasLejana(base);
      break;
    }
    case 5:
    {
      int opcionTipo;
      do
      {
        printMenuTipoConexion();
        cin >> opcionTipo;

        switch (opcionTipo)
        {
        case 1:
          printTitulo("Árbol de Expansión Mínima (por distancia)");
          grafo.prim(1);
          break;
        case 2:
          printTitulo("Árbol de Expansión Mínima (por vuelos)");
          grafo.prim(2);
          break;
        case 0:
          printOK("Volviendo al menú anterior...");
          break;
        default:
          printError("Opción inválida. Intente de nuevo.");
        }
      } while (opcionTipo != 0);
      break;
    }
    case 6:
      printTitulo("Información de Ciudades Sede");
      grafo.mostrarCiudades();
      break;
    case 7:
    {
      string origen, destino;
      float peso;
      int tipo;
      cout << CYAN << "Código IATA origen: " << RESET;
      cin >> origen;
      cout << CYAN << "Código IATA destino: " << RESET;
      cin >> destino;
      cout << CYAN << "Tipo (1: Distancia, 2: Vuelos): " << RESET;
      cin >> tipo;
      cout << CYAN << "Valor: " << RESET;
      cin >> peso;
      grafo.agregarArista(origen, destino, peso, tipo);
      printOK("Conexión agregada correctamente.");
      break;
    }
    case 0:
      printOK("Volviendo al menú principal...");
      break;
    default:
      printError("Opción inválida. Intente de nuevo.");
    }
  } while (opcion != 0);
}

int main()
{
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  cout << BOLD << GREEN << "CWD: " << cwd << RESET << endl;

  // Inicializar estructuras
  ArbolAVL arbol;
  Grafo grafo;

  // Carga inicial
  CSVManager::cargarCSV(arbol, "../data/sedes.csv");
  printOK("Sedes cargadas desde CSV.");

  grafo.cargarCiudadesDesdeCSV("../data/sedes.csv");
  grafo.cargarAristasDesdeCSV("../data/conexiones.csv");
  grafo.cargarVuelosDiariosDesdeCSV("../data/conexiones2.csv");
  printOK("Grafo de conexiones cargado desde CSV.");

  int opcionPrincipal;
  do
  {
    printMenuPrincipal();
    cin >> opcionPrincipal;

    switch (opcionPrincipal)
    {
    case 1:
      menuSedes(arbol);
      break;
    case 2:
      menuGrafo(grafo);
      break;
    case 0:
      printOK("Guardando cambios...");
      CSVManager::guardarCSV(arbol, "../data/sedes.csv");
      grafo.guardarEnCSV("../data/conexiones.csv");
      grafo.guardarEnCSV("../data/conexiones2.csv");
      printOK("Archivos guardados. ¡Hasta luego!");
      break;
    default:
      printError("Opción inválida. Intente de nuevo.");
    }
  } while (opcionPrincipal != 0);

  return 0;
}
