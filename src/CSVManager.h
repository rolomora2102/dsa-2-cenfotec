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
  static void cargarCSV(ArbolAVL &arbol, string filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo: " << filename << endl;
      return;
    }

    string linea;
    getline(archivo, linea);
    int lineNumber = 1;

    while (getline(archivo, linea)) {
      ++lineNumber;
      stringstream ss(linea);
      string campo;
      string datos[7];
      int i = 0;

      while (getline(ss, campo, ',') && i < 7) {
        datos[i++] = campo;
      }

      if (i < 7) {
        cerr << "Warning: línea " << lineNumber << " incompleta: '" << linea
             << "'" << endl;
        continue;
      }

      int capacidad = 0;
      int anio = 0;

      try {
        if (datos[5].empty())
          throw invalid_argument("Capacidad vacía");
        capacidad = stoi(datos[5]);
      } catch (const std::exception &e) {
        cerr << "Error en línea " << lineNumber << ": capacidad inválida '"
             << datos[5] << "'" << endl;
        continue;
      }

      try {
        if (datos[6].empty())
          throw invalid_argument("Año vacío");
        anio = stoi(datos[6]);
      } catch (const std::exception &e) {
        cerr << "Error en línea " << lineNumber << ": año inválido '"
             << datos[6] << "'" << endl;
        continue;
      }

      arbol.insertar(datos[0], datos[1], datos[2], datos[3], datos[4],
                     capacidad, anio);
    }
    archivo.close();
  }

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

  static void cargarConexiones(Grafo &grafo, string filename) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo de conexiones: " << filename << endl;
      return;
    }

    string linea;
    getline(archivo, linea);
    int lineNumber = 1;
    while (getline(archivo, linea)) {
      ++lineNumber;
      stringstream ss(linea);
      string origen, destino, pesoStr, tipoStr;

      if (getline(ss, origen, ',') && getline(ss, destino, ',') &&
          getline(ss, pesoStr, ',')) {

        float peso = 0.0f;
        try {
          peso = stof(pesoStr);
        } catch (...) {
          cerr << "Error: peso inválido en línea " << lineNumber << ": '"
               << pesoStr << "'" << endl;
          continue;
        }

        int tipo = 1;

        if (getline(ss, tipoStr, ',')) {
          tipoStr.erase(0, tipoStr.find_first_not_of(" \t\r\n"));
          tipoStr.erase(tipoStr.find_last_not_of(" \t\r\n") + 1);

          if (!tipoStr.empty()) {
            try {
              tipo = stoi(tipoStr);
            } catch (...) {
              cerr << "Warning: tipo inválido en línea " << lineNumber << ": '"
                   << tipoStr << "'. Usando tipo=1 por defecto." << endl;
              tipo = 1;
            }
          }
        }

        grafo.agregarArista(origen, destino, peso, tipo);
      } else {
        cerr << "Warning: línea mal formateada en línea " << lineNumber << ": '"
             << linea << "'" << endl;
      }
    }
    archivo.close();
  }

  static void guardarConexiones(Grafo &grafo, string filename) {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
      cerr << "No se pudo abrir el archivo para guardar conexiones: "
           << filename << endl;
      return;
    }

    archivo << "origen,destino,peso\n";
    grafo.guardarEnCSV(filename);
    archivo.close();
  }
};

#endif
