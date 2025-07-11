# 📂 Proyecto AVL — Mundial 2026

Este proyecto implementa un árbol **AVL** para gestionar sedes de estadios usando **C++ puro**.  
Toda la lógica de inserción, búsqueda, eliminación y recorrido está desarrollada desde cero **sin librerías externas de estructuras de datos**.

---

## 🚀 Estructura del proyecto

/ProyectoRoot/
├── build/ # Binario compilado vive aquí
├── data/sedes.csv # Archivo CSV con las sedes
├── docs/ # Documentación (justificación, UML, uso)
├── src/
│ ├── main.cpp
│ ├── ArbolAVL.h
│ ├── Nodo.h
│ ├── CSVManager.h
│ ├── print_helpers.h
└── README.md

---

## ⚡ Rutas y ejecución

- El árbol carga y guarda `../data/sedes.csv` relativo a la carpeta `build/`:
  - Esto significa que **el binario debe ejecutarse parado dentro de `build/`**.
- Por eso:
  - Si corres desde terminal:  
    ```bash
    cd build
    ./main
    ```
  - Si usas **Neovim + Overseer**: asegúrate de que tu tarea haga `cd build && ./main`.

- En **CLion (JetBrains)**:
  - Ve a `Run > Edit Configurations`  
  - Cambia **Working Directory** a la raíz del proyecto **o** a la carpeta de build (`cmake-build-debug`).  
  - Asegúrate de que tu ruta en el código sea:
    ```cpp
    CSVManager::cargarCSV(arbol, "../data/sedes.csv");
    ```

- En **Visual Studio**:
  - Click derecho en el proyecto → Properties → Debugging.
  - Cambia **Working Directory** a tu carpeta de build (`Debug/` o `Release/`).

---

## 🟢 Librerías utilizadas

- **C++ Standard Library** (`<iostream>`, `<fstream>`, `<string>`).
- **ANSI Colors Helpers**: Se usaron macros y funciones helper (`print_helpers.h`) para imprimir mensajes coloridos en terminal.
- ✅ **No se utiliza ninguna librería externa de estructuras de datos, árboles o grafos.**
- ✅ Todo balanceo, inserción y eliminación está programado a mano.
- 📌 `print_helpers.h` es solo para salida formateada, no afecta la lógica del árbol.

---

## 📝 Justificación de dependencias

- Este proyecto respeta la consigna: **la estructura del árbol no se apoya en librerías externas**.
- El único extra es el uso de **ANSI Escape Codes** para salida amigable.
- Esto funciona igual en terminal, Visual Studio, CLion y cualquier IDE sin instalaciones especiales.

---

## ⚙️ Compilación

Ejemplo para compilar manual:
```bash
# Desde la raíz del proyecto:
g++ src/*.cpp -o build/main
