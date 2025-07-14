#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "Nodo.h"
#include "print_helpers.h" // Para colores y helpers
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ArbolAVL {
private:
    Nodo* raiz;

    // ------------------------------
    // Métodos auxiliares de balanceo
    // ------------------------------

    int obtenerAltura(Nodo* nodo) {
        return (nodo == nullptr) ? 0 : nodo->altura;
    }

    int obtenerBalance(Nodo* nodo) {
        return (nodo == nullptr) ? 0 : obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izquierda;
        Nodo* T2 = x->derecha;

        x->derecha = y;
        y->izquierda = T2;

        y->altura = 1 + max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha));
        x->altura = 1 + max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha));

        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->derecha;
        Nodo* T2 = y->izquierda;

        y->izquierda = x;
        x->derecha = T2;

        x->altura = 1 + max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha));
        y->altura = 1 + max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha));

        return y;
    }

    // ------------------------------
    // Inserción balanceada
    // ------------------------------
    Nodo* insertar(Nodo* nodo, Nodo* nuevoNodo) {
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

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
        int balance = obtenerBalance(nodo);

        // Casos de rotación
        if (balance > 1 && nuevoNodo->codigoIATA < nodo->izquierda->codigoIATA)
            return rotarDerecha(nodo);
        if (balance < -1 && nuevoNodo->codigoIATA > nodo->derecha->codigoIATA)
            return rotarIzquierda(nodo);
        if (balance > 1 && nuevoNodo->codigoIATA > nodo->izquierda->codigoIATA) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && nuevoNodo->codigoIATA < nodo->derecha->codigoIATA) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // ------------------------------
    // Eliminación balanceada
    // ------------------------------
    Nodo* eliminar(Nodo* nodo, string codigo) {
        if (nodo == nullptr) {
            printError("Sede no encontrada para eliminar.");
            return nodo;
        }

        if (codigo < nodo->codigoIATA)
            nodo->izquierda = eliminar(nodo->izquierda, codigo);
        else if (codigo > nodo->codigoIATA)
            nodo->derecha = eliminar(nodo->derecha, codigo);
        else {
            if (nodo->izquierda == nullptr || nodo->derecha == nullptr) {
                Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else
                    *nodo = *temp;
                delete temp;
            } else {
                Nodo* sucesor = nodo->derecha;
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
        }

        if (nodo == nullptr)
            return nodo;

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0)
            return rotarDerecha(nodo);
        if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecha) <= 0)
            return rotarIzquierda(nodo);
        if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // ------------------------------
    // Recorridos auxiliares
    // ------------------------------
    void inOrder(Nodo* nodo) {
        if (nodo != nullptr) {
            inOrder(nodo->izquierda);
            mostrarNodo(nodo);
            inOrder(nodo->derecha);
        }
    }

    void listarPorPais(Nodo* nodo, const string& paisBuscado) {
        if (nodo != nullptr) {
            listarPorPais(nodo->izquierda, paisBuscado);
            if (nodo->pais == paisBuscado)
                mostrarNodo(nodo);
            listarPorPais(nodo->derecha, paisBuscado);
        }
    }

    void listarPorCapacidad(Nodo* nodo, int capMin) {
        if (nodo != nullptr) {
            listarPorCapacidad(nodo->izquierda, capMin);
            if (nodo->capacidad >= capMin)
                mostrarNodo(nodo);
            listarPorCapacidad(nodo->derecha, capMin);
        }
    }

    void llenarVector(Nodo* nodo, vector<Nodo*>& lista) {
        if (nodo != nullptr) {
            llenarVector(nodo->izquierda, lista);
            lista.push_back(nodo);
            llenarVector(nodo->derecha, lista);
        }
    }

    Nodo* buscar(Nodo* nodo, string codigo) {
        if (nodo == nullptr || nodo->codigoIATA == codigo)
            return nodo;
        if (codigo < nodo->codigoIATA)
            return buscar(nodo->izquierda, codigo);
        else
            return buscar(nodo->derecha, codigo);
    }

    void guardarEnCSV(Nodo* nodo, ofstream& archivo) {
        if (nodo != nullptr) {
            guardarEnCSV(nodo->izquierda, archivo);
            archivo << nodo->codigoIATA << "," << nodo->pais << "," << nodo->ciudad
                    << "," << nodo->estadioFIFA << "," << nodo->estadioOficial
                    << "," << nodo->capacidad << "," << nodo->anio << "\n";
            guardarEnCSV(nodo->derecha, archivo);
        }
    }

public:
    ArbolAVL() { raiz = nullptr; }

    // Inserción pública
    void insertar(string codigo, string pais, string ciudad, string estFIFA, string estOficial, int cap, int anio) {
        Nodo* nuevoNodo = new Nodo(codigo, pais, ciudad, estFIFA, estOficial, cap, anio);
        raiz = insertar(raiz, nuevoNodo);
    }

    // Buscar
    Nodo* buscar(string codigo) {
        return buscar(raiz, codigo);
    }

    // Eliminar
    void eliminar(string codigo) {
        raiz = eliminar(raiz, codigo);
    }

    // Recorridos públicos
    void inOrder() {
        inOrder(raiz);
    }

    void listarPorPais(const string& paisBuscado) {
        printTitulo("Sedes en el país: " + paisBuscado);
        listarPorPais(raiz, paisBuscado);
    }

    void listarPorCapacidad(int capMin) {
        printTitulo("Sedes con capacidad ≥ " + to_string(capMin));
        listarPorCapacidad(raiz, capMin);
    }

    void listarOrdenadoPorAnio() {
        printTitulo("Sedes ordenadas por año de inauguración");
        vector<Nodo*> lista;
        llenarVector(raiz, lista);
        sort(lista.begin(), lista.end(), [](Nodo* a, Nodo* b) { return a->anio < b->anio; });
        for (Nodo* n : lista)
            mostrarNodo(n);
    }

    // Guardar CSV
    void guardarEnCSV(ofstream& archivo) {
        guardarEnCSV(raiz, archivo);
    }

    // Mostrar nodo
    void mostrarNodo(Nodo* nodo);
};

#endif
