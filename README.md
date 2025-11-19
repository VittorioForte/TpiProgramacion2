# Sistema de Gestión de Kartódromo

Trabajo práctico de Programación II: sistema de consola en C++ para administrar un kartódromo, con gestión de **clientes**, **carreras**, **pagos** y **listados e informes** (podios históricos y recaudación mensual/anual), usando **archivos binarios** como persistencia.

---

## 0. Detalles técnicos del proyecto (para futuros desarrolladores)

### 0.1. Lenguaje, estándar y entorno esperado

- **Lenguaje:** C++ (estilo clásico, cercano a C con algunas cosas de C++).
- **Estándar mínimo recomendado:** C++11.
- **Sistema operativo objetivo:** Windows  
  - Se usan `windows.h`, `system("cls")`, `system("pause")`.
- **Tipo de proyecto:** Aplicación de consola monolítica con múltiples `.cpp/.h` y un solo ejecutable.

---

### 0.2. Librerías y headers usados

#### Librerías estándar

- `#include <iostream>` → `std::cout`, `std::cin`.
- `#include <cstdio>` → `FILE*`, `fopen`, `fclose`, `fwrite`, `fread`, `fseek`, `ftell`.
- `#include <cstdlib>` → `system("cls")`, `system("pause")`.
- `#include <cstring>` → `strcpy`, `strncpy`, manejo de `char[]`.
- `#include <string>` → `std::string`, conversiones básicas.
- `#include <ctime>` → uso puntual (semillas/tiempo).
- `#include <windows.h>` → `SetConsoleTextAttribute` (colores de consola).

#### Librerías de terceros / propias

- `#include "rlutil.h"`  
  Librería header-only para manejo de consola:
  - Posición del cursor: `rlutil::locate(x, y)`.
  - Colores: `rlutil::setBackgroundColor`, `rlutil::setColor`.
  - Limpieza: `rlutil::cls()`.

#### Headers propios (modelo, persistencia y menús)

- Modelo / dominio:
  - `"Clientes.h"`, `"Categorias.h"`, `"Fecha.h"`, `"Hora.h"`
  - `"Participantes.h"`, `"Carrera.h"`, `"Pago.h"`
- Persistencia:
  - `"ArchivoClientes.h"`, `"ArchivoCarreras.h"`, `"ArchivoPagos.h"`
- Menús:
  - `"MenuClientes.h"`, `"MenuCarreras.h"`, `"MenuPagos.h"`, `"MenuListados.h"`

---

### 0.3. Persistencia y manejo de archivos (`*.dat`)

No se usa base de datos. Toda la información se guarda en **archivos binarios**:

- `clientes.dat` → objetos `Cliente`
- `carreras.dat` → objetos `Carrera`
- `pagos.dat` → objetos `Pago`

Patrón usado en las clases `Archivo*`:

- Abrir archivo:

```cpp
FILE* p = fopen(_nombreArchivo.c_str(), "ab");   // agregar
FILE* p = fopen(_nombreArchivo.c_str(), "rb");   // leer
FILE* p = fopen(_nombreArchivo.c_str(), "rb+");  // leer/escribir en pos

* Búsquedas secuenciales:

  * Se recorre el archivo de principio a fin leyendo registro por registro y comparando claves (DNI, ID, etc.).

> Importante:
> Las clases almacenadas en archivos **no deben tener punteros ni estructuras dinámicas complejas**. Se trabaja con tipos simples y `char[]` porque se hace un dump binario directo de la clase.

---

### 0.4. Memoria dinámica y estructuras usadas

* No se usa `std::vector`, `new`/`delete`, ni smart pointers.
* El modelo principal trabaja con:

  * Instancias locales (en stack).
  * Arrays de tamaño fijo.
* Ejemplo:

  * `Carrera` contiene: `Participantes _listaResultados[10];`
    (máximo 10 participantes por carrera).
* Cuando se necesita acumular datos para informes (podios históricos, recaudación), se usan arrays simples dimensionados con un máximo razonable.

En resumen: la “persistencia extendida” se hace en archivos `.dat`, y en memoria sólo se manejan estructuras simples y arrays.

---

### 0.5. Estilo de código

* **Clases:** PascalCase → `Cliente`, `Carrera`, `ArchivoClientes`, `MenuPagos`.
* **Miembros privados:** prefijo `_` → `_idCliente`, `_nombre`, `_estado`.
* **Métodos:** lowerCamelCase → `cargar`, `mostrar`, `getIdCliente`, `setEstado`, `cargarResultados`.
* **Idioma:** español en variables y métodos (`cargar`, `mostrar`, `BuscarPorDNI`, `CantidadRegistros`, `menuCarreras`).
* **Formato:**

  * Indentación de 4 espacios.
  * `using namespace std;` en casi todos los `.cpp`.
  * Llaves habitualmente en la misma línea del encabezado (`if (...) {`).
* **UI en consola:**

  * `rlutil::locate` para alinear columnas.
  * Encabezados con colores de fondo.
  * Separadores con líneas de guiones.
  * Menús con numeración clara y mensajes tipo:
    `"Seleccione una opcion:"`.

---

### 0.6. Arquitectura por capas / módulos

* **Dominio (modelo):**

  * `Cliente`, `Carrera`, `Pago`, `Categorias`, `Participantes`, `Fecha`, `Hora`.
* **Persistencia (acceso a datos):**

  * `ArchivoClientes`, `ArchivoCarreras`, `ArchivoPagos`.
* **Presentación (interfaz de consola):**

  * `MenuClientes`, `MenuCarreras`, `MenuPagos`, `MenuListados`.
* **Punto de entrada:**

  * `main.cpp` → muestra el menú principal y delega en los submenús.

Extender el proyecto:

* Nueva lógica de negocio → agregar métodos a las clases de dominio.
* Nuevas operaciones sobre archivos → ampliar las clases `Archivo*`.
* Nuevas opciones de usuario → agregar opciones en el menú correspondiente.

---

## 0.7. Compilación y ejecución

Requisitos mínimos:

* Windows.
* Compilador C++ (por ejemplo MinGW/g++, o el que trae Code::Blocks).
* Incluir `rlutil.h` en el proyecto (ya está en el repositorio).

Ejemplo genérico de compilación con g++ (asumiendo todos los `.cpp`):

```bash
g++ *.cpp -o Kartodromo.exe
```

En entornos como Code::Blocks / Dev-C++:

* Crear un proyecto de consola.
* Agregar todos los `.cpp` del repositorio al proyecto.
* Asegurarse de que `rlutil.h` esté en el mismo directorio o en el include path.
* Compilar y ejecutar desde el IDE.

---

## 1. Qué hace este proyecto

Es un **sistema de gestión de kartódromo** en C++ por consola que permite:

* Administrar **clientes**.
* Administrar **carreras** (categoría, fecha, hora, participantes, resultados).
* Registrar y consultar **pagos**.
* Generar **informes/listados**:

  * Podios históricos por categoría (mejores tiempos de vuelta).
  * Recaudación mensual y total anual.

Toda la información se guarda en **archivos binarios**:

* `clientes.dat`
* `carreras.dat`
* `pagos.dat`

---

## 2. Estructura general del sistema

### 2.1. Menú principal (`main.cpp`)

Menú principal:

1. Clientes
2. Carreras
3. Pagos
4. Listados e Informes
5. Salir

Según la opción seleccionada se llama a:

* `menuClientes()`
* `menuCarreras()`
* `menuPagos()`
* `menuListados()`

El diseño usa `rlutil` y `windows.h` para limpiar pantalla, aplicar colores y ubicar texto en columnas.

---

## 3. Modelo de datos (clases principales)

### 3.1. Cliente + ArchivoClientes

**`Cliente`**

Atributos:

* `_idCliente`
* `_nombre`, `_apellido`
* `_telefono`
* `_dni`
* `_estado` (bool) → alta lógica (true = activo, false = “eliminado”)

Métodos:

* `cargar()`, `mostrar(int fila)`
* Getters: ID, DNI, nombre, apellido, estado.
* Setters: ID y estado.

**`ArchivoClientes`**

Encapsula el acceso a `clientes.dat`:

* `bool Guardar(Cliente)`
* `bool Guardar(Cliente, int pos)`
* `Cliente Leer(int pos)`
* `int BuscarPorDNI(int dni)`
* `int BuscarPorID(int id)`
* `int CantidadRegistros()`
* `void LeerTodos(int cant, Cliente* vector)`

---

### 3.2. Categorías

**`Categorias`**

Define el tipo de carrera:

* `_estado`
* `_idCategoria` (1 = PROFESIONAL, 2 = AMATEUR, 3 = INFANTIL)
* `_cantVueltas`
* `_nombreCat`
* `_precio` (monto a cobrar por esa categoría)

Métodos:

* Getters: estado, id, vueltas, nombre, precio.
* Setters: estado, id, nombre (asigna id/vueltas/precio según el nombre), vueltas.
* `cargar()` → pide el nombre de categoría y configura el resto.
* `mostrar()` → imprime los datos de la categoría.

---

### 3.3. Fecha y Hora

**`Fecha`**

* `_dia`, `_mes`, `_anio`
* `Cargar()`, `toString()`
* Getters/setters simples.

**`Hora`**

* `_hora`, `_minuto`
* `cargar()`, `toString()`
* `getTotalMinutos()` → convierte hora:minuto a total de minutos (para restar tiempos).

---

### 3.4. Participantes

**`Participantes`**

Representa cada piloto dentro de una carrera:

* `_nombre`
* `_horaFinal` (duración total en minutos)
* `_tiempoVueltas` (promedio por vuelta en minutos)

Métodos:

* Setters de nombre, horaFinal, tiempoVueltas.
* Getters correspondientes.
* `mostrarResultado()` → imprime nombre, tiempo total y promedio.

> Los participantes **no se guardan en archivo propio**: están embebidos en la clase `Carrera` mediante un array fijo.

---

### 3.5. Carrera + ArchivoCarreras

**`Carrera`**

Atributos:

* `_idCarrera`
* `_categoria` (`Categorias`)
* `_fecha` (`Fecha`)
* `_horaInicio` (`Hora`)
* `_cantParticipantes`
* `_listaResultados[10]` (`Participantes`)
* `_idClienteResponsable`
* `_estado` (bool) → alta lógica (no se borra físicamente del archivo).
* `_estadoCarrera` (0 = pendiente, 1 = finalizada)

Métodos principales:

* `cargar()`
  Pide:

  * Categoría (`_categoria.cargar()`).
  * Fecha (`_fecha.Cargar()`).
  * Hora de inicio (`_horaInicio.cargar()`).
  * Cantidad de participantes (max 10) y nombre de cada participante.
    Deja la carrera como **pendiente** (sin tiempos cargados).

* `mostrar(int fila, ArchivoClientes& archClientes) const`
  Imprime una fila con:

  * ID de carrera.
  * Estado: `PENDIENTE` o `TERMINADA`.
  * Categoría, cantidad de vueltas, hora de inicio.
  * Cliente responsable (buscado por ID en `ArchivoClientes`).

  Además:

  * Si la carrera está pendiente, debajo lista los nombres de los participantes.
  * Si la carrera está terminada, se puede mostrar el podio usando `mostrarTop3()`.

* `cargarResultados()`
  Para cada participante:

  * Pide hora de finalización.
  * Valida que sea posterior a la hora de inicio.
  * Calcula duración total en minutos.
  * Calcula tiempo promedio por vuelta (duración / cantidad de vueltas).
  * Guarda ambos datos en el objeto `Participantes`.

  Luego:

  * Llama a `ordenarResultadosPorTiempo()` para ordenar según el mejor tiempo promedio.
  * Setea `_estadoCarrera = 1`.

* `mostrarTop3() const`
  Imprime el TOP 3 de participantes según el orden actual (ordenados por tiempo de vuelta).

* `ordenarResultadosPorTiempo()`
  Ordena el array `_listaResultados` por `getTiempoVueltas()` (menor primero).

* Setters:

  * `setIdCarrera(int idCarrera)`
  * `setIdClienteResponsable(int idClienteResponsable)`
  * `setEstado(bool estado)`

* Getters:

  * `getIdCarrera() const`
  * `getEstado() const`
  * `getIdClienteResponsable() const`
  * `getEstadoCarrera() const`
  * `getFecha() const`
  * `getHoraInicio() const`
  * `getCategoria() const`
  * `getCantParticipantes() const`
  * `const Participantes& getParticipante(int index) const`

**`ArchivoCarreras`**

Maneja `carreras.dat`:

* `bool Guardar(Carrera)`
* `bool Guardar(Carrera, int pos)`
* `Carrera Leer(int pos)`
* `int Buscar(int idCarrera)`
* `int CantidadRegistros()`
* `void Leer(int cantidadRegistros, Carrera* vector)`

---

### 3.6. Pago + ArchivoPagos

**`Pago`**

Atributos:

* `_idPago`
* `_idCarrera`
* `_idCliente`
* `_monto` (int)
* `_estado` (bool) → si el pago está activo/registrado
* `_fechaPago` (`Fecha`)

Métodos:

* Getters:

  * `getIdPago() const`
  * `getIdCarrera() const`
  * `getIdCliente() const`
  * `getMonto() const`
  * `getEstado() const`
  * `getFechaPago() const`

* Setters:

  * `setIdPago(int idPago)`
  * `setIdCarrera(int idCarrera)`
  * `setIdCliente(int idCliente)`
  * `setMonto(int monto)`
  * `setEstado(bool estado)`
  * `setFechaPago(const Fecha& fechaPago)`

* `mostrar(int fila, ArchivoCarreras& archCarreras, ArchivoClientes& archClientes) const`
  Imprime:

  * ID del pago.
  * Monto.
  * Fecha de pago.
  * Categoría + ID de la carrera correspondiente.
  * Nombre y apellido del cliente (buscado por ID).

**`ArchivoPagos`**

Maneja `pagos.dat`:

* `bool Guardar(Pago)`
* `bool Guardar(Pago, int pos)`
* `Pago Leer(int pos)`
* `int BuscarPorCarrera(int idCarrera)`
* `int CantidadRegistros()`

---

## 4. Lógica de los menús

### 4.1. Menú de clientes (`menuClientes`)

Opciones:

1. Registrar nuevo cliente
2. Listar todos los clientes
3. Buscar cliente por DNI
4. Modificar cliente
5. Eliminar cliente (baja lógica)
6. Volver

Flujo:

* **Alta de cliente:**

  * `Cliente c; c.cargar();`
  * ID = `CantidadRegistros() + 1`.
  * Se guarda en `clientes.dat`.

* **Listado de clientes:**

  * Muestra sólo los clientes con `_estado == true` en una tabla.

* **Buscar por DNI:**

  * Usa `ArchivoClientes::BuscarPorDNI`.
  * Si existe, muestra ese cliente.

* **Modificar cliente:**

  * Busca por DNI.
  * Muestra datos actuales.
  * Vuelve a llamar a `c.cargar()` y sobrescribe en la misma posición.

* **Eliminar cliente:**

  * Busca por DNI.
  * Setea `_estado = false` y guarda (baja lógica).

> Existe una función interna `mostrarHistorialPagosCliente` que recorre los pagos de un cliente y muestra carreras, fechas y montos, pero en esta versión no está conectada directamente al menú.

---

### 4.2. Menú de carreras (`menuCarreras`)

Opciones:

1. Nueva carrera
2. Listar carreras
3. Buscar carrera por número
4. Eliminar carrera (baja lógica)
5. Finalizar carrera (cargar resultados)
6. Volver

Flujo de **alta de carrera** (opción 1):

1. Se crea `Carrera c;` y se llama a `c.cargar()`.

2. Se pregunta si el cliente responsable ya existe:

   * Si **sí**:

     * Se pide DNI.
     * Se busca en `clientes.dat` con `BuscarPorDNI`.
     * Si existe, se usa su ID como responsable.
     * Si no existe, la carrera queda sin responsable.
   * Si **no**:

     * Se carga un nuevo cliente.
     * Se asigna ID = `CantidadRegistros() + 1`.
     * Se guarda y se usa como responsable.

3. Se asigna ID a la carrera:
   `idCarrera = ArchivoCarreras::CantidadRegistros() + 1;`
   y se guarda en `carreras.dat`.

4. Si hay responsable (ID distinto de 0), se genera **automáticamente un pago**:

   * `idPago = ArchivoPagos::CantidadRegistros() + 1`.
   * `idCarrera = id asignado a la carrera`.
   * `idCliente = id del responsable`.
   * `monto = c.getCategoria().getPrecio()`.
   * `fechaPago = c.getFecha()`.
   * `estado = true`.
   * Se guarda en `pagos.dat`.

Resto de opciones:

* **Listar carreras (2):**
  Recorre `carreras.dat` y muestra sólo las activas (`getEstado()`), usando `Carrera::mostrar`.

* **Buscar carrera por ID (3):**
  Usa `ArchivoCarreras::Buscar`. Si la carrera existe y está activa, se muestra.

* **Eliminar carrera (4):**

  * Busca por ID.
  * Muestra la carrera.
  * Pide confirmación.
  * Setea `_estado = false` y guarda (baja lógica).

* **Finalizar carrera (5):**

  * Busca por ID.
  * Verifica que no esté eliminada.
  * Verifica que no esté ya finalizada (`getEstadoCarrera()`).
  * Llama a `c.cargarResultados()` para registrar tiempos.
  * Guarda la carrera actualizada como finalizada.

---

### 4.3. Menú de pagos (`menuPagos`)

Opciones:

1. Lista de pagos
2. Historial por cliente
3. Filtro por categoría
4. Volver

Flujo:

* **1) Lista de pagos**

  * Carga cantidad total de registros.
  * Si no hay, muestra mensaje.
  * Si hay:

    * Dibuja encabezado de tabla.
    * Recorre todos los pagos.
    * Muestra sólo los pagos con `_estado == true` usando `Pago::mostrar`.

* **2) Historial por cliente**

  * Pide DNI del cliente.
  * Lo busca en `clientes.dat`.
  * Si lo encuentra:

    * Recorre `pagos.dat`.
    * Muestra todos los pagos activos (`getEstado()`) donde `getIdCliente()` coincide con el ID del cliente encontrado.

* **3) Filtro por categoría**

  * Pide el nombre de la categoría (`PROFESIONAL / AMATEUR / INFANTIL`).
  * Recorre todos los pagos activos.
  * Para cada pago:

    * Busca la carrera asociada (`ArchivoCarreras::Buscar` + `Leer`).
    * Obtiene el nombre de la categoría de esa carrera.
    * Si coincide con el nombre buscado, muestra el pago.

---

### 4.4. Menú de listados e informes (`menuListados`)

Funciones internas:

* `class RegistroTiempo`
  Estructura auxiliar con:

  * `char _nombre[50];`
  * `double _tiempoVuelta;`
  * `char _fecha[20];`
  * `int _idCarrera;`

* `ordenarPorTiempo(RegistroTiempo[], int cantidad)`
  Ordena los registros por `_tiempoVuelta` (menor a mayor).

* `listarPodioCategoria(ArchivoCarreras&, int idCategoria, const char* nombreCat)`

  * Recorre todas las carreras.
  * Filtra:

    * carreras activas (`getEstado()`),
    * finalizadas (`getEstadoCarrera() == 1`),
    * de la categoría indicada.
  * De cada participante genera un `RegistroTiempo` con:

    * nombre,
    * mejor tiempo de vuelta (`getTiempoVueltas()`),
    * fecha en texto (`Fecha::toString()`),
    * ID de la carrera.
  * Ordena la lista por tiempo de vuelta.
  * Muestra un **Top 3 histórico** para esa categoría.

* `mostrarRecaudacionMensual(ArchivoPagos&)`

  * Recorre todos los pagos activos.
  * Usa el mes de `FechaPago` (`getFechaPago().getMes()`).
  * Acumula montos en `recaudacion[1..12]`.
  * Calcula `totalGeneral` con la suma anual.
  * Muestra:

    * Recaudación por mes (nombre del mes + monto).
    * Total recaudado en el año.

**`menuListados()`**

Opciones:

1. Podios históricos por categoría
2. Recaudación mensual y total anual
3. Volver

* Opción 1:

  * Llama a:

    * `listarPodioCategoria(archivoCarreras, 1, "PROFESIONAL");`
    * `listarPodioCategoria(archivoCarreras, 2, "AMATEUR");`
    * `listarPodioCategoria(archivoCarreras, 3, "INFANTIL");`

* Opción 2:

  * Llama a `mostrarRecaudacionMensual(archivoPagos);`

---

## 5. Resumen final

Este proyecto es un **sistema completo de gestión de un kartódromo**, con:

* Modelo orientado a objetos:

  * `Cliente`, `Carrera`, `Pago`, `Categorias`, `Participantes`, `Fecha`, `Hora`.
* Persistencia binaria mediante archivos `.dat` y clases `Archivo*`.
* ABM de clientes y carreras, con **bajas lógicas**.
* Generación de pagos automáticos al registrar carreras con responsable.
* Módulo de pagos:

  * Listado general.
  * Historial por cliente.
  * Filtro por categoría.
* Módulo de informes:

  * **Podios históricos** por tiempo de vuelta y categoría.
  * **Recaudación mensual y anual** a partir de los pagos.

```
```
