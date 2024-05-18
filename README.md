# Philosopher Project - 42
## Descripción
El proyecto Philosopher es parte del plan de estudios de la escuela 42 y está diseñado para poner a prueba tus habilidades en la programación concurrente y la gestión de recursos. El proyecto simula el problema clásico de los filósofos comensales, una metáfora que ilustra los desafíos en la programación concurrente, como la evitación de la inanición y la prevención de interbloqueos.

## Tabla de Contenidos
Descripción
Tabla de Contenidos
Requisitos
Instalación
Uso
Algoritmo
Ejemplos
Créditos

## Requisitos
Para compilar y ejecutar este proyecto, necesitas:

Un compilador compatible con C (por ejemplo, gcc)
Una máquina con un sistema operativo Unix (Linux, macOS, etc.)

## Instalación
Para instalar y compilar el proyecto, sigue estos pasos:

Clona el repositorio:

```bash
git clone https://github.com/tu_usuario/philosopher.git
cd philosopher
```
Compila el proyecto:

```bash
make
```
## Uso
Para ejecutar el programa, usa el siguiente comando:

```bash
./philosopher <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]
```

<number_of_philosophers>: Número de filósofos y tenedores.
<time_to_die>: Tiempo en milisegundos que un filósofo puede estar sin comer antes de morir.
<time_to_eat>: Tiempo en milisegundos que toma a un filósofo comer.
<time_to_sleep>: Tiempo en milisegundos que un filósofo pasa durmiendo.
[<number_of_times_each_philosopher_must_eat>]: (Opcional) Número de veces que cada filósofo debe comer antes de que el programa termine. Si no se especifica, el programa correrá indefinidamente.

## Ejemplo:

```bash
./philosopher 5 800 200 200 7
```
## Algoritmo
El problema de los filósofos comensales se resuelve utilizando hilos (threads) y mutexes para evitar condiciones de carrera y garantizar que no ocurra un interbloqueo. Cada filósofo alterna entre los estados de pensar, comer y dormir, siguiendo estas reglas:

Un filósofo solo puede comer si tiene ambos tenedores (el de su izquierda y el de su derecha).
Después de comer, el filósofo coloca los tenedores de vuelta en la mesa y procede a dormir.
Después de dormir, el filósofo vuelve a pensar.
Si un filósofo no puede comer durante el time_to_die, el programa termina y reporta que el filósofo ha muerto.
## Ejemplos
Aquí hay algunos ejemplos de cómo ejecutar el programa:

Cinco filósofos, cada uno con 800ms antes de morir, 200ms para comer, 200ms para dormir, sin límite de comidas:

```bash
./philosopher 5 800 200 200
```
Cinco filósofos, cada uno con 800ms antes de morir, 200ms para comer, 200ms para dormir, cada uno debe comer al menos 7 veces:

```bash
./philosopher 5 800 200 200 7
```
## Créditos
Este proyecto fue realizado como parte del currículo de la escuela 42. Para más información sobre la escuela y sus programas, visita 42's official website.
