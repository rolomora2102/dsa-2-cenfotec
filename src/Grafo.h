// grafo.h
#ifndef GRAFO_H
#define GRAFO_H
#include "graphs/graphs.hpp"
#include "tabulate/tabulate.hpp"
using namespace tabulate;

#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

class Arista {
public:
  string destino;
  float peso;
  int tipo; // 1: distancia geográfica, 2: vuelos directos (ejemplo)

  Arista() : destino(""), peso(0), tipo(1) {}
  Arista(const string &d, float p, int t = 1) : destino(d), peso(p), tipo(t) {}
};

class NodoAdyacente {
public:
  Arista arista;
  NodoAdyacente *siguiente;

  NodoAdyacente() : arista(), siguiente(nullptr) {}
  NodoAdyacente(const Arista &a, NodoAdyacente *sig = nullptr)
      : arista(a), siguiente(sig) {}
};

class ListaAdyacencia {
public:
  string codigoIATA;
  NodoAdyacente *inicio;

  ListaAdyacencia() : codigoIATA(""), inicio(nullptr) {}
};

class Ciudad {
public:
  string codigoIATA;
  string pais;
  string nombreCiudad;
  string estadioFIFA;
  string estadioOficial;
  int capacidadEstadio;
  int anioInauguracion;

  Ciudad()
      : codigoIATA(""), pais(""), nombreCiudad(""), estadioFIFA(""),
        estadioOficial(""), capacidadEstadio(0), anioInauguracion(0) {}
};

class Grafo {
private:
  static const int MAX_VERTICES = 50;
  ListaAdyacencia vertices[MAX_VERTICES];
  Ciudad ciudades[MAX_VERTICES];
  int numVertices;

  int encontrarIndice(const string &codigo) {
    for (int i = 0; i < numVertices; ++i) {
      if (vertices[i].codigoIATA == codigo)
        return i;
    }
    return -1;
  }

public:
  Grafo() {
    numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; ++i) {
      vertices[i].inicio = nullptr;
    }
  }

  void agregarVertice(const string &codigoIATA) {
    if (encontrarIndice(codigoIATA) == -1 && numVertices < MAX_VERTICES) {
      vertices[numVertices].codigoIATA = codigoIATA;
      vertices[numVertices].inicio = nullptr;
      ++numVertices;
    }
  }

  void agregarCiudad(const Ciudad &ciudad) {
    int idx = encontrarIndice(ciudad.codigoIATA);
    if (idx == -1) {
      if (numVertices < MAX_VERTICES) {
        vertices[numVertices].codigoIATA = ciudad.codigoIATA;
        vertices[numVertices].inicio = nullptr;
        ciudades[numVertices] = ciudad;
        ++numVertices;
      }
    } else {
      ciudades[idx] = ciudad;
    }
  }

  void agregarArista(const string &origen, const string &destino, float peso,
                     int tipo = 1) {
    agregarVertice(origen);
    agregarVertice(destino);

    int i = encontrarIndice(origen);
    NodoAdyacente *nuevo =
        new NodoAdyacente{{destino, peso, tipo}, vertices[i].inicio};
    vertices[i].inicio = nuevo;

    int j = encontrarIndice(destino);
    NodoAdyacente *nuevo2 =
        new NodoAdyacente{{origen, peso, tipo}, vertices[j].inicio};
    vertices[j].inicio = nuevo2;
  }

  void mostrarGrafo() {
    using namespace graphs;

    const int MAX_NODOS = 50; // Máximo de nodos según tu definición de Grafo
    const int MAX_CONEXIONES = 100; // Máximo estimado de conexiones

    struct Punto {
      long double x;
      long double y;
    };

    struct GraficoData {
      int num_puntos_tipo1;
      int num_puntos_tipo2;
      Punto puntos_tipo1[MAX_CONEXIONES][2];
      Punto puntos_tipo2[MAX_CONEXIONES][2];
      int num_nodos;
      Punto nodos[MAX_NODOS];
    };

    GraficoData datos;
    datos.num_puntos_tipo1 = 0;
    datos.num_puntos_tipo2 = 0;
    datos.num_nodos = numVertices;

    // Asignar coordenadas circulares a los nodos
    long double angle = 0;
    const long double angle_step = 2 * M_PI / numVertices;
    for (int i = 0; i < numVertices; ++i) {
      datos.nodos[i].x = cos(angle) * 10;
      datos.nodos[i].y = sin(angle) * 10;
      angle += angle_step;
    }

    // Procesar conexiones (aristas)
    for (int i = 0; i < numVertices; ++i) {
      NodoAdyacente *actual = vertices[i].inicio;
      while (actual != nullptr) {
        // Encontrar índice del destino
        int idx_destino = -1;
        for (int j = 0; j < numVertices; ++j) {
          if (vertices[j].codigoIATA == actual->arista.destino) {
            idx_destino = j;
            break;
          }
        }

        if (idx_destino != -1 && i < idx_destino) {
          if (actual->arista.tipo == 1 &&
              datos.num_puntos_tipo1 < MAX_CONEXIONES) {
            datos.puntos_tipo1[datos.num_puntos_tipo1][0] = datos.nodos[i];
            datos.puntos_tipo1[datos.num_puntos_tipo1][1] =
                datos.nodos[idx_destino];
            datos.num_puntos_tipo1++;
          } else if (actual->arista.tipo == 2 &&
                     datos.num_puntos_tipo2 < MAX_CONEXIONES) {
            datos.puntos_tipo2[datos.num_puntos_tipo2][0] = datos.nodos[i];
            datos.puntos_tipo2[datos.num_puntos_tipo2][1] =
                datos.nodos[idx_destino];
            datos.num_puntos_tipo2++;
          }
        }

        actual = actual->siguiente;
      }
    }

    // Opciones para nodos (todos iguales)
    options opts_nodos;
    opts_nodos.title = "Grafo de Conexiones";
    opts_nodos.color = color_blue;
    opts_nodos.type = type_braille;
    opts_nodos.mark = mark_plus;
    opts_nodos.style = style_light;

    // Dibujar nodos
    for (int i = 0; i < datos.num_nodos; i++) {
      long double x = datos.nodos[i].x;
      long double y = datos.nodos[i].y;
      graphs::function_1<long double>(
          24, 80, 0, 10000, 0, 10000,
          [x, y](long double) -> long double { return y; }, opts_nodos);
    }

    // Opciones para tipo 1 (por ejemplo, distancia geográfica)
    options opts_tipo1 = opts_nodos;
    opts_tipo1.color = color_green; // color verde para tipo 1

    // Opciones para tipo 2 (por ejemplo, vuelos directos)
    options opts_tipo2 = opts_nodos;
    opts_tipo2.color = color_red; // color rojo para tipo 2

    // Dibujar aristas tipo 1
    for (int i = 0; i < datos.num_puntos_tipo1; i++) {
      long double x1 = datos.puntos_tipo1[i][0].x;
      long double y1 = datos.puntos_tipo1[i][0].y;
      long double x2 = datos.puntos_tipo1[i][1].x;
      long double y2 = datos.puntos_tipo1[i][1].y;

      graphs::function_1<long double>(
          24, 80, 0, 10000, 0, 10000,
          [x1, x2, y1, y2](long double x) -> long double {
            if (x2 == x1)
              return (x == x1) ? y1
                               : std::numeric_limits<long double>::quiet_NaN();
            long double m = (y2 - y1) / (x2 - x1);
            long double b = y1 - m * x1;
            return m * x + b;
          },
          opts_tipo1);
    }

    // Dibujar aristas tipo 2
    for (int i = 0; i < datos.num_puntos_tipo2; i++) {
      long double x1 = datos.puntos_tipo2[i][0].x;
      long double y1 = datos.puntos_tipo2[i][0].y;
      long double x2 = datos.puntos_tipo2[i][1].x;
      long double y2 = datos.puntos_tipo2[i][1].y;

      graphs::function_1<long double>(
          24, 80, 0, 10000, 0, 10000,
          [x1, x2, y1, y2](long double x) -> long double {
            if (x2 == x1)
              return (x == x1) ? y1
                               : std::numeric_limits<long double>::quiet_NaN();
            long double m = (y2 - y1) / (x2 - x1);
            long double b = y1 - m * x1;
            return m * x + b;
          },
          opts_tipo2);
    }

    // Leyenda
    printf("\nLeyenda:\n");
    printf("● Nodos (ciudades)\n");
    printf("─ Aristas tipo 1 (distancia geográfica) [verde]\n");
    printf("─ Aristas tipo 2 (vuelos directos) [rojo]\n");

    // Mostrar ciudades con su código
    printf("\nCiudades:\n");
    for (int i = 0; i < numVertices; ++i) {
      printf("%s: %s\n", vertices[i].codigoIATA.c_str(),
             ciudades[i].nombreCiudad.c_str());
    }
  }

  void dijkstra(const string &origen) {
    float dist[MAX_VERTICES];
    bool visitado[MAX_VERTICES] = {false};
    int origenIdx = encontrarIndice(origen);

    for (int i = 0; i < numVertices; ++i) {
      dist[i] = numeric_limits<float>::infinity();
    }
    dist[origenIdx] = 0;

    for (int i = 0; i < numVertices; ++i) {
      int u = -1;
      float minDist = numeric_limits<float>::infinity();
      for (int j = 0; j < numVertices; ++j) {
        if (!visitado[j] && dist[j] < minDist) {
          minDist = dist[j];
          u = j;
        }
      }

      if (u == -1)
        break;
      visitado[u] = true;

      NodoAdyacente *actual = vertices[u].inicio;
      while (actual != nullptr) {
        int v = encontrarIndice(actual->arista.destino);
        if (!visitado[v] && dist[u] + actual->arista.peso < dist[v]) {
          dist[v] = dist[u] + actual->arista.peso;
        }
        actual = actual->siguiente;
      }
    }

    cout << "\nDistancias desde " << origen << ":\n";
    for (int i = 0; i < numVertices; ++i) {
      cout << origen << " -> " << vertices[i].codigoIATA << ": " << dist[i]
           << endl;
    }
  }

  void prim() {
    bool enMST[MAX_VERTICES] = {false};
    float clave[MAX_VERTICES];
    int padre[MAX_VERTICES];

    for (int i = 0; i < numVertices; ++i) {
      clave[i] = numeric_limits<float>::infinity();
      padre[i] = -1;
    }
    clave[0] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
      float min = numeric_limits<float>::infinity();
      int u = -1;
      for (int v = 0; v < numVertices; ++v) {
        if (!enMST[v] && clave[v] < min) {
          min = clave[v];
          u = v;
        }
      }

      if (u == -1)
        break;
      enMST[u] = true;

      NodoAdyacente *actual = vertices[u].inicio;
      while (actual != nullptr) {
        int v = encontrarIndice(actual->arista.destino);
        if (!enMST[v] && actual->arista.peso < clave[v]) {
          clave[v] = actual->arista.peso;
          padre[v] = u;
        }
        actual = actual->siguiente;
      }
    }

    float pesoTotal = 0;
    cout << "\nÁrbol de Expansión Mínima (Prim):\n";
    for (int i = 1; i < numVertices; ++i) {
      if (padre[i] != -1) {
        cout << vertices[padre[i]].codigoIATA << " - " << vertices[i].codigoIATA
             << " (" << clave[i] << ")\n";
        pesoTotal += clave[i];
      }
    }
    cout << "\nPeso total del árbol: " << pesoTotal << endl;
  }

  void cargarDesdeCSV(const string &archivoPath) {
    ifstream archivo(archivoPath);
    string linea;
    while (getline(archivo, linea)) {
      size_t pos1 = linea.find(',');
      size_t pos2 = linea.rfind(',');
      string origen = linea.substr(0, pos1);
      string destino = linea.substr(pos1 + 1, pos2 - pos1 - 1);
      float peso = atof(linea.substr(pos2 + 1).c_str());
      agregarArista(origen, destino, peso);
    }
    archivo.close();
  }

  void cargarCiudadesDesdeCSV(const string &archivoPath) {
    ifstream archivo(archivoPath);
    string linea;
    bool primeraLinea = true;
    while (getline(archivo, linea)) {
      if (primeraLinea) { // Saltar encabezado
        primeraLinea = false;
        continue;
      }

      Ciudad ciudad;
      size_t pos = 0;
      string campos[7];
      int campoIdx = 0;

      while ((pos = linea.find(',')) != string::npos && campoIdx < 6) {
        campos[campoIdx++] = linea.substr(0, pos);
        linea.erase(0, pos + 1);
      }
      campos[campoIdx] = linea; // Último campo

      ciudad.codigoIATA = campos[0];
      ciudad.pais = campos[1];
      ciudad.nombreCiudad = campos[2];
      ciudad.estadioFIFA = campos[3];
      ciudad.estadioOficial = campos[4];
      ciudad.capacidadEstadio = atoi(campos[5].c_str());
      ciudad.anioInauguracion = atoi(campos[6].c_str());

      agregarVertice(ciudad.codigoIATA); // Asegura que exista el vértice
      agregarCiudad(ciudad);
    }
    archivo.close();
  }

  void guardarEnCSV(const string &archivoPath) {
    ofstream archivo(archivoPath);
    for (int i = 0; i < numVertices; ++i) {
      NodoAdyacente *actual = vertices[i].inicio;
      while (actual != nullptr) {
        if (vertices[i].codigoIATA < actual->arista.destino) {
          archivo << vertices[i].codigoIATA << "," << actual->arista.destino
                  << "," << actual->arista.peso << "\n";
        }
        actual = actual->siguiente;
      }
    }
    archivo.close();
  }

  void mostrarCiudades() {
    Table table;
    table.add_row({"Ciudad", "Codigo IATA", "Pais", "Estadio FIFA",
                   "Estadio Oficial", "Capacidad", "Año Inauguracion"});

    for (int i = 0; i < numVertices; ++i) {
      table.add_row({ciudades[i].nombreCiudad, ciudades[i].codigoIATA,
                     ciudades[i].pais, ciudades[i].estadioFIFA,
                     ciudades[i].estadioOficial,
                     to_string(ciudades[i].capacidadEstadio),
                     to_string(ciudades[i].anioInauguracion)});
    }

    // Opciones de estilo
    table.format()
        .font_style({FontStyle::bold})
        .border_color(Color::green)
        .corner("•");

    cout << table << endl;
  }
  void cargarAristasDesdeCSV(const string &archivoPath) {
    ifstream archivo(archivoPath);
    string linea;
    getline(archivo, linea); // saltar encabezado
    while (getline(archivo, linea)) {
      size_t pos1 = linea.find(',');
      size_t pos2 = linea.find(',', pos1 + 1);
      if (pos1 == string::npos || pos2 == string::npos)
        continue;

      string origen = linea.substr(0, pos1);
      string destino = linea.substr(pos1 + 1, pos2 - pos1 - 1);
      float peso = stof(linea.substr(pos2 + 1));

      agregarArista(origen, destino, peso);
    }
    archivo.close();
  }

  // Función para encontrar la sede más lejana desde una base
  void encontrarSedeMasLejana(const string &origen) {
    float dist[MAX_VERTICES];
    bool visitado[MAX_VERTICES] = {false};
    int origenIdx = encontrarIndice(origen);

    if (origenIdx == -1) {
      cout << "Sede de origen no encontrada." << endl;
      return;
    }

    // Inicializar distancias
    for (int i = 0; i < numVertices; ++i) {
      dist[i] = numeric_limits<float>::infinity();
    }
    dist[origenIdx] = 0;

    // Algoritmo de Dijkstra
    for (int i = 0; i < numVertices; ++i) {
      int u = -1;
      float minDist = numeric_limits<float>::infinity();
      for (int j = 0; j < numVertices; ++j) {
        if (!visitado[j] && dist[j] < minDist) {
          minDist = dist[j];
          u = j;
        }
      }

      if (u == -1)
        break;
      visitado[u] = true;

      NodoAdyacente *actual = vertices[u].inicio;
      while (actual != nullptr) {
        int v = encontrarIndice(actual->arista.destino);
        if (!visitado[v] && dist[u] + actual->arista.peso < dist[v]) {
          dist[v] = dist[u] + actual->arista.peso;
        }
        actual = actual->siguiente;
      }
    }

    // Encontrar la distancia máxima
    float maxDist = 0;
    int sedeMaxIdx = -1;
    for (int i = 0; i < numVertices; ++i) {
      if (dist[i] != numeric_limits<float>::infinity() && dist[i] > maxDist) {
        maxDist = dist[i];
        sedeMaxIdx = i;
      }
    }

    if (sedeMaxIdx != -1) {
      cout << "\n=== SEDE MÁS LEJANA ===" << endl;
      cout << "Desde: " << origen << " (" << ciudades[origenIdx].nombreCiudad
           << ")" << endl;
      cout << "Hasta: " << vertices[sedeMaxIdx].codigoIATA << " ("
           << ciudades[sedeMaxIdx].nombreCiudad << ")" << endl;
      cout << "Distancia: " << maxDist << " km" << endl;
      cout << "País destino: " << ciudades[sedeMaxIdx].pais << endl;
    } else {
      cout << "No se encontraron sedes conectadas." << endl;
    }
  }

  // Función para mostrar ruta específica entre dos sedes
  void mostrarRutaEspecifica(const string &origen, const string &destino) {
    float dist[MAX_VERTICES];
    int padre[MAX_VERTICES];
    bool visitado[MAX_VERTICES] = {false};
    int origenIdx = encontrarIndice(origen);
    int destinoIdx = encontrarIndice(destino);

    if (origenIdx == -1 || destinoIdx == -1) {
      cout << "Una o ambas sedes no fueron encontradas." << endl;
      return;
    }

    // Inicializar
    for (int i = 0; i < numVertices; ++i) {
      dist[i] = numeric_limits<float>::infinity();
      padre[i] = -1;
    }
    dist[origenIdx] = 0;

    // Dijkstra con seguimiento de padre
    for (int i = 0; i < numVertices; ++i) {
      int u = -1;
      float minDist = numeric_limits<float>::infinity();
      for (int j = 0; j < numVertices; ++j) {
        if (!visitado[j] && dist[j] < minDist) {
          minDist = dist[j];
          u = j;
        }
      }

      if (u == -1)
        break;
      visitado[u] = true;

      NodoAdyacente *actual = vertices[u].inicio;
      while (actual != nullptr) {
        int v = encontrarIndice(actual->arista.destino);
        if (!visitado[v] && dist[u] + actual->arista.peso < dist[v]) {
          dist[v] = dist[u] + actual->arista.peso;
          padre[v] = u;
        }
        actual = actual->siguiente;
      }
    }

    // Mostrar ruta
    cout << "\n=== RUTA MÁS CORTA ===" << endl;
    cout << "De: " << origen << " a " << destino << endl;
    cout << "Distancia total: " << dist[destinoIdx] << " km" << endl;

    // Reconstruir camino
    cout << "Ruta: ";
    int camino[MAX_VERTICES];
    int longitud = 0;
    int actual = destinoIdx;

    while (actual != -1) {
      camino[longitud++] = actual;
      actual = padre[actual];
    }

    for (int i = longitud - 1; i >= 0; --i) {
      cout << vertices[camino[i]].codigoIATA;
      if (i > 0)
        cout << " -> ";
    }
    cout << endl;
  }
};

#endif
