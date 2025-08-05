#ifndef CSVMANAGER_H
#define CSVMANAGER_H

#include "ArbolAVL.h"
#include "Grafo.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class CSVManager {
public:
  // Cargar datos desde CSV al árbol AVL
  static void cargarCSV(ArbolAVL &arbol, string filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo: " << filename << endl;
      return;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
      stringstream ss(linea);
      string campo;
      string datos[7];
      int i = 0;

      while (getline(ss, campo, ',') && i < 7) {
        datos[i++] = campo;
      }

      // Parsear int para capacidad y año
      int capacidad = stoi(datos[5]);
      int anio = stoi(datos[6]);

      arbol.insertar(datos[0], datos[1], datos[2], datos[3], datos[4],
                     capacidad, anio);
    }
    archivo.close();
  }

  // Guardar árbol en CSV
  static void guardarCSV(ArbolAVL &arbol, string filename) {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo para guardar: " << filename << endl;
      return;
    }

    archivo << "IATA,País,Ciudad,Estadio FIFA,Estadio Oficial,Capacidad,Año\n";
    arbol.guardarEnCSV(archivo);
    archivo.close();
  }

  // Cargar conexiones del grafo desde CSV
  static void cargarConexiones(Grafo &grafo, string filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo de conexiones: " << filename << endl;
      return;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
      stringstream ss(linea);
      string origen, destino, pesoStr;

      if (getline(ss, origen, ',') && getline(ss, destino, ',') &&
          getline(ss, pesoStr, ',')) {

        float peso = stof(pesoStr);
        grafo.agregarArista(origen, destino, peso);
      }
    }
    archivo.close();
  }

  // Guardar conexiones del grafo en CSV
  static void guardarConexiones(Grafo &grafo, string filename) {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo para guardar conexiones: "
           << filename << endl;
      return;
    }

    archivo << "origen,destino,peso\n";
    grafo.guardarEnCSV(filename); // Usar el método existente de tu grafo
    archivo.close();
  }
};

#endif
