# Snake Game in C

A classic Snake game developed in C for the console, featuring persistent high scores and progressive difficulty.

## Features
- WASD controls (no need to press Enter for input)
- Food system: eat `*` to grow and score points
- Current score and *highscore* persistently saved in `highscore.txt`
- Snake grows when eating food
- Collision detection with the snake's own tail (game over)
- Screen wrapping: going out one side makes you appear on the opposite side
- Progressive speed: the game gets faster each time you eat
- Post-game menu: option to play again or quit
- Reverse direction lock (you cannot turn 180°)

## Controls
| Key | Action |
|-----|--------|
| W   | Up     |
| A   | Left   |
| S   | Down   |
| D   | Right  |

## Requirements
- GCC compiler (MinGW recommended on Windows)
- Standard C libraries + `conio.h` (keyboard input) and `unistd.h` (speed control, included in MinGW)

## Build and Run
1. Compile the source code (`sanke.c`):
```bash
gcc sanke.c -o sanke
```
2. Run:
```bash
sanke.exe
```

*Note: Designed for Windows due to the use of `conio.h` and `system("cls").`*

## How to Play
- Move the snake (head `0`, tail `o`) to eat the food `*`
- Avoid colliding with your own tail
- On losing, a new highscore is automatically saved if you beat the previous one

---

# Juego Snake en C

Un clásico juego de la serpiente desarrollado en C para consola, con récord persistente y dificultad progresiva.

## Características
- Controles con WASD (entrada sin necesidad de presionar Enter)
- Sistema de comida: come `*` para crecer y sumar puntos
- Puntaje actual y *highscore* guardado persistentemente en `highscore.txt`
- Crecimiento de la serpiente al comer
- Detección de colisiones con la propia cola (game over)
- Teletransporte en bordes: salir por un lado del tablero aparece por el opuesto
- Velocidad progresiva: el juego se acelera cada vez que comes
- Menú post-game: opción para jugar otra vez o salir
- Bloqueo de dirección inversa (no puedes girar 180°)

## Controles
| Tecla | Acción |
|-------|--------|
| W     | Arriba |
| A     | Izquierda |
| S     | Abajo |
| D     | Derecha |

## Requisitos
- Compilador GCC (se recomienda MinGW en Windows)
- Librerías estándar de C + `conio.h` (entrada de teclado) y `unistd.h` (control de velocidad, incluido en MinGW)

## Compilar y ejecutar
1. Compilar el código fuente (`sanke.c`):
```bash
gcc sanke.c -o sanke
```
2. Ejecutar:
```bash
sanke.exe
```

*Nota: Diseñado para Windows por el uso de `conio.h` y `system("cls").`*

## Cómo jugar
- Mueve la serpiente (cabeza `0`, cola `o`) para comer la comida `*`
- Evita chocar con tu propia cola
- Al perder, se guarda automáticamente el nuevo récord si superas el anterior