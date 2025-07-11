# 📄 Guía de Uso

## ⚙️ Cómo compilar

### ✅ Manual desde terminal:
```bash
g++ src/*.cpp -o build/main
```
### IDE
🚀 Cómo ejecutar

    Terminal:

cd build
./main

CLion (JetBrains):

    Run > Edit Configurations

    Cambia Working Directory a cmake-build-debug/.

Visual Studio:

    Project Properties > Debugging > Working Directory a Debug/.

📌 Uso del programa

1️⃣ Carga de sedes:
El programa lee ../data/sedes.csv al iniciar.

2️⃣ Menú interactivo:

    Insertar nueva sede

    Buscar sede

    Modificar sede

    Eliminar sede

    Listar sedes en recorrido in-order

    Guardar y salir

3️⃣ Persistencia:
Al salir, se guardan automáticamente los cambios en el CSV.
🟢 Detalles importantes

    Ejecuta siempre parado en build/ para que ../data/sedes.csv se resuelva correctamente.

    Si corres desde la raíz, asegúrate de cd build antes de ./main.

📁 Archivo de salida

    Los cambios se sobrescriben en data/sedes.csv para mantener persistencia entre ejecuciones.

🫡 Soporte

Para cualquier duda:

    Revisa print_helpers.h para modificar estilos de impresión.

    Si surgen problemas de rutas, confirma tu Working Directory.

---

## ✅ **Y el `UML.png`?**

Ese debe ser **un diagrama de clases simple**:

[Nodo]
├── codigoIATA : string
├── pais : string
├── ciudad : string
├── estadioFIFA : string
├── estadioOficial : string
├── capacidad : int
├── anio : int
├── izquierda : Nodo*
├── derecha : Nodo*
├── altura : int

[ArbolAVL]
├── raiz : Nodo*
├── insertar()
├── buscar()
├── mostrarNodo()
├── eliminar()
├── inOrder()
├── guardarEnCSV()

[CSVManager]
├── cargarCSV()
├── guardarCSV()


✅ Lo puedes dibujar en draw.io, PlantUML o Figma y exportarlo como `UML.png`.

---

## 🏁 **Todo listo**

- `README.md` → correr y dependencias.  
- `justificacion.md` → por qué no usas libs de árboles y por qué los colores no violan nada.  
- `uso.md` → paso a paso para compilar y ejecutar.

---

Si quieres, dime y armamos el `UML.puml` o el esquema en texto para que lo exportes fácil. ¿Lo quieres crack? 🚀
