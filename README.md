# UNIVERSIDAD NACIONAL SAN AGUSTÍN DE AREQUIPA

# ESCUELA PROFESIONAL DE INGENIERÍA DE SISTEMAS

## TECNOLOGÍA DE OBJETOS

## SOLID

## Estudiantes:

Camargo Hilachoque, Romina Giuliana  
Hatches Curo, José León Enrique  
Mayta Quispe, Paola Adamari  
Morocco Saico, José Manuel

## Docente:

Diego Alonso Iquira Becerra

**Grupo: C**

**3er Año - 2026 - B**

## Descripción

Guía Práctica 05: aplicación de los principios SOLID en un sistema de gestión de reservas de hotel.

Los ejercicios 01 al 05 se desarrollan y ejecutan de forma independiente. El ejercicio 06 reúne los principios en una aplicación integrada.

**Lenguaje:** C++17.

## Estructura del proyecto

```text
TO_Practica05_SOLID/
├── 01_SRP/
│   └── src/
│       └── main.cpp
├── 02_OCP/
│   └── src/
│       └── main.cpp
├── 03_LSP/
│   └── src/
│       └── main.cpp
├── 04_ISP/
│   └── src/
│       └── main.cpp
├── 05_DIP/
│   └── src/
│       └── main.cpp
├── 06_Integracion_SOLID/
│   └── src/
│       └── main.cpp
└── README.md
```

## Distribución del trabajo

- **Persona 1 — Ejercicio 01 (SRP):** separar la disponibilidad de `Habitacion` mediante `GestorDisponibilidadHabitacion`.
- **Persona 2 — Ejercicio 02 (OCP):** implementar políticas de cancelación Flexible, Moderada y Estricta mediante una interfaz.
- **Persona 3 — Ejercicio 03 (LSP):** implementar subclases de `Habitacion` respetando el contrato de la clase base y demostrar polimorfismo.
- **Persona 4 — Ejercicios 04 (ISP) y 05 (DIP):** dividir las interfaces de servicios e implementar notificaciones mediante inyección de dependencias.
- **Todos — Ejercicio 06:** integrar los principios SOLID en el sistema de reservas.

## Requisitos

- Compilador `g++` compatible con C++17.
- Terminal Linux, macOS o Git Bash en Windows.

Ejecutar los siguientes comandos **desde la raíz del repositorio**.

# Compilar

## 1. 01_SRP/

```bash
g++ -std=c++17 01_SRP/src/*.cpp -o 01_SRP/ejercicio
```

## 2. 02_OCP/

```bash
g++ -std=c++17 02_OCP/src/*.cpp -o 02_OCP/ejercicio
```

## 3. 03_LSP/

```bash
g++ -std=c++17 03_LSP/src/*.cpp -o 03_LSP/ejercicio
```

## 4. 04_ISP/

```bash
g++ -std=c++17 04_ISP/src/*.cpp -o 04_ISP/ejercicio
```

## 5. 05_DIP/

```bash
g++ -std=c++17 05_DIP/src/*.cpp -o 05_DIP/ejercicio
```

## 6. 06_Integracion_SOLID/

```bash
g++ -std=c++17 06_Integracion_SOLID/src/*.cpp -o 06_Integracion_SOLID/ejercicio
```

# Ejecutar

## 1. 01_SRP/

```bash
./01_SRP/ejercicio
```

## 2. 02_OCP/

```bash
./02_OCP/ejercicio
```

## 3. 03_LSP/

```bash
./03_LSP/ejercicio
```

## 4. 04_ISP/

```bash
./04_ISP/ejercicio
```

## 5. 05_DIP/

```bash
./05_DIP/ejercicio
```

## 6. 06_Integracion_SOLID/

```bash
./06_Integracion_SOLID/ejercicio
```

> **Estado inicial:** cada carpeta contiene un `main.cpp` provisional, únicamente para comprobar la compilación y ejecución. La implementación de los ejercicios está pendiente.
