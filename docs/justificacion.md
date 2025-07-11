# 📄 Justificación del Proyecto

Este proyecto implementa un **Árbol AVL** como estructura principal para gestionar información de las sedes del Mundial 2026.  
Toda la lógica de inserción, búsqueda, eliminación y recorrido ha sido programada **desde cero**, sin utilizar librerías externas de grafos, árboles o estructuras de datos avanzadas.

---

## 📌 Elección de herramientas

- **Lenguaje:** C++  
  - Ofrece control total de punteros, estructuras dinámicas y manejo eficiente de memoria.
- **Persistencia:** Archivo CSV (`data/sedes.csv`)  
  - Es un formato simple, portable y fácil de manipular.
- **Organización:**  
  - La lógica se divide en clases: `Nodo`, `ArbolAVL` y `CSVManager` para modularidad.
  - Se usa `print_helpers.h` para salida formateada, sin afectar la lógica del árbol.

---

## ✅ Por qué no usamos librerías externas

Se evitó deliberadamente usar librerías que implementen árboles, balanceos o grafos, para cumplir con la consigna de **desarrollar la estructura AVL manualmente**, garantizando:
- Aprendizaje real de inserción, eliminación y rotaciones.
- Control total del balanceo.
- Flexibilidad para futuras ampliaciones.

---

## ⚡ Justificación de librerías auxiliares

- Se utiliza la librería estándar de C++ (`<iostream>`, `<fstream>`, `<string>`) para entrada/salida y manejo de archivos.
- `print_helpers.h` implementa códigos ANSI para colores, 100% compatibles con terminal y sin dependencias externas.

---

## 🫡 Conclusión

El resultado es un proyecto portable, extensible y fácil de probar en terminal o IDE, dejando la base lista para que el balanceo AVL se implemente y se optimice posteriormente.
