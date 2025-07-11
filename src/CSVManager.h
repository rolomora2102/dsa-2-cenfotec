#ifndef CSVMANAGER_H
#define CSVMANAGER_H

#include "ArbolAVL.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class CSVManager {
public:
  // Cargar datos desde CSV
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
};

#endif
