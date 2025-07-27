// grafo.h
#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <limits>
using namespace std;

struct Arista {
    string destino;
    float peso;
};

struct NodoAdyacente {
    Arista arista;
    NodoAdyacente* siguiente;
};

struct ListaAdyacencia {
    string codigoIATA;
    NodoAdyacente* inicio;
};

struct Ciudad {
    string codigoIATA;
    string pais;
    string nombreCiudad;
    string estadioFIFA;
    string estadioOficial;
    int capacidadEstadio;
    int anioInauguracion;
};

class Grafo {
private:
    static const int MAX_VERTICES = 50;
    ListaAdyacencia vertices[MAX_VERTICES];
    Ciudad ciudades[MAX_VERTICES];
    int numVertices;

    int encontrarIndice(const string& codigo) {
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

    void agregarVertice(const string& codigoIATA) {
        if (encontrarIndice(codigoIATA) == -1 && numVertices < MAX_VERTICES) {
            vertices[numVertices].codigoIATA = codigoIATA;
            vertices[numVertices].inicio = nullptr;
            ++numVertices;
        }
    }

    void agregarCiudad(const Ciudad& ciudad) {
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

    void agregarArista(const string& origen, const string& destino, float peso) {
        agregarVertice(origen);
        agregarVertice(destino);

        int i = encontrarIndice(origen);
        NodoAdyacente* nuevo = new NodoAdyacente{{destino, peso}, vertices[i].inicio};
        vertices[i].inicio = nuevo;

        int j = encontrarIndice(destino);
        NodoAdyacente* nuevo2 = new NodoAdyacente{{origen, peso}, vertices[j].inicio};
        vertices[j].inicio = nuevo2;
    }

    void mostrarGrafo() {
        for (int i = 0; i < numVertices; ++i) {
            cout << vertices[i].codigoIATA << " -> ";
            NodoAdyacente* actual = vertices[i].inicio;
            while (actual != nullptr) {
                cout << actual->arista.destino << "(" << actual->arista.peso << ") ";
                actual = actual->siguiente;
            }
            cout << endl;
        }
    }

    void dijkstra(const string& origen) {
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

            if (u == -1) break;
            visitado[u] = true;

            NodoAdyacente* actual = vertices[u].inicio;
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
            cout << origen << " -> " << vertices[i].codigoIATA << ": " << dist[i] << endl;
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

            if (u == -1) break;
            enMST[u] = true;

            NodoAdyacente* actual = vertices[u].inicio;
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
                cout << vertices[padre[i]].codigoIATA << " - " << vertices[i].codigoIATA << " (" << clave[i] << ")\n";
                pesoTotal += clave[i];
            }
        }
        cout << "\nPeso total del árbol: " << pesoTotal << endl;
    }

    void cargarDesdeCSV(const string& archivoPath) {
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

    void cargarCiudadesDesdeCSV(const string& archivoPath) {
        ifstream archivo(archivoPath);
        string linea;
        bool primeraLinea = true;
        while (getline(archivo, linea)) {
            if (primeraLinea) {  // Saltar encabezado
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

            agregarVertice(ciudad.codigoIATA);  // Asegura que exista el vértice
            agregarCiudad(ciudad);
        }
        archivo.close();
    }

    void guardarEnCSV(const string& archivoPath) {
        ofstream archivo(archivoPath);
        for (int i = 0; i < numVertices; ++i) {
            NodoAdyacente* actual = vertices[i].inicio;
            while (actual != nullptr) {
                if (vertices[i].codigoIATA < actual->arista.destino) {
                    archivo << vertices[i].codigoIATA << "," << actual->arista.destino << "," << actual->arista.peso << "\n";
                }
                actual = actual->siguiente;
            }
        }
        archivo.close();
    }

    void mostrarCiudades() {
        for (int i = 0; i < numVertices; ++i) {
            cout << "Ciudad: " << ciudades[i].nombreCiudad 
                << ", Codigo IATA: " << ciudades[i].codigoIATA
                << ", Pais: " << ciudades[i].pais
                << ", Estadio FIFA: " << ciudades[i].estadioFIFA
                << ", Estadio Oficial: " << ciudades[i].estadioOficial
                << ", Capacidad: " << ciudades[i].capacidadEstadio
                << ", Año Inauguracion: " << ciudades[i].anioInauguracion
                << endl;
        }
    }

    void cargarAristasDesdeCSV(const string& archivoPath) {
        ifstream archivo(archivoPath);
        string linea;
        getline(archivo, linea); // saltar encabezado
        while (getline(archivo, linea)) {
            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);
            if (pos1 == string::npos || pos2 == string::npos) continue;

            string origen = linea.substr(0, pos1);
            string destino = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            float peso = stof(linea.substr(pos2 + 1));

            agregarArista(origen, destino, peso);
        }
        archivo.close();
    }

    // Función para encontrar la sede más lejana desde una base
    void encontrarSedeMasLejana(const string& origen) {
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

            if (u == -1) break;
            visitado[u] = true;

            NodoAdyacente* actual = vertices[u].inicio;
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
            cout << "Desde: " << origen << " (" << ciudades[origenIdx].nombreCiudad << ")" << endl;
            cout << "Hasta: " << vertices[sedeMaxIdx].codigoIATA << " (" << ciudades[sedeMaxIdx].nombreCiudad << ")" << endl;
            cout << "Distancia: " << maxDist << " km" << endl;
            cout << "País destino: " << ciudades[sedeMaxIdx].pais << endl;
        } else {
            cout << "No se encontraron sedes conectadas." << endl;
        }
    }

    // Función para mostrar ruta específica entre dos sedes
    void mostrarRutaEspecifica(const string& origen, const string& destino) {
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

            if (u == -1) break;
            visitado[u] = true;

            NodoAdyacente* actual = vertices[u].inicio;
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
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }

};

#endif
