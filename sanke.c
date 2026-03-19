// ================= LIBRERÍAS =================
#include <stdio.h>      // printf, scanf
#include <stdbool.h>    // tipo bool (true / false)
#include <stdlib.h>     // rand(), srand()
#include <unistd.h>     // usleep()
#include <conio.h>      // getch(), kbhit() (teclas sin enter)
#include <time.h>       // time() para números aleatorios

// ================= CONSTANTES =================
#define anchoTablero 20
#define altoTablero 20

// ================= VARIABLES GLOBALES =================
int highscore = 0;          // puntaje máximo guardado
int score = 0;              // puntaje actual

int snakeX = 0, snakeY = 0; // posición de la cabeza
int foodX = 0, foodY = 0;   // posición de la comida

int snakeCola = 0;          // tamaño de la cola
int velocidad = 200000;     // velocidad del juego (menos = más rápido)

// arreglos para guardar la cola
int tailX[100];
int tailY[100];

bool gameover = false;      // estado del juego

// ================= DIRECCIONES =================
enum moveSerpiente {
	stop,
	left,
	right,
	up,
	down
};

enum moveSerpiente dir;     // dirección actual

// ================= ARCHIVOS =================

// carga el highscore desde archivo
void cargarHighscore(){
	FILE *file = fopen("highscore.txt", "r");
	
	if (file != NULL){
		fscanf(file, "%d", &highscore);
		fclose(file);
	}
}
	
// guarda el highscore en archivo
void guardarHighscore(){
	FILE *file = fopen("highscore.txt", "w");
	
	if (file != NULL){
		fprintf(file, "%d", highscore);
		fclose(file);
	}
}

// ================= LÓGICA DEL JUEGO =================
void logic (){
	
	// guardar posición anterior de la cabeza
	int prevX = snakeX;
	int prevY = snakeY;
	
	// mover la cola hacia atrás (todos siguen al anterior)
	for (int i = snakeCola - 1; i > 0; i--){
		tailX[i] = tailX[i-1];
		tailY[i] = tailY[i-1];
	}
	
	// la primera parte de la cola sigue a la cabeza
	tailX[0] = prevX;
	tailY[0] = prevY;
	
	// movimiento según dirección
	if (dir == left){
		snakeX--;
	}
	else if (dir == right){
		snakeX++;
	}
	else if (dir == up){
		snakeY--;
	}
	else if (dir == down){
		snakeY++;
	}
	
	// ================= TELETRANSPORTE (bordes) =================
	if (snakeX < 0){
		snakeX = anchoTablero - 1;
	}
	else if (snakeX >= anchoTablero){
		snakeX = 0;
	}
	
	if (snakeY < 0){
		snakeY = altoTablero - 1;
	}
	else if (snakeY >= altoTablero){
		snakeY = 0;
	}
	
	// ================= COMER COMIDA =================
	if (snakeX == foodX && snakeY == foodY){
		score++;            // aumenta puntaje
		snakeCola++;        // crece la cola
		
		// nueva comida aleatoria
		foodX = rand() % anchoTablero;
		foodY = rand() % altoTablero;
		
		// aumenta velocidad
		if (velocidad > 50000){
			velocidad -= 10000;
		}
	}
	
	// ================= COLISIÓN CON LA COLA =================
	for (int i = 0; i < snakeCola; i++){
		if (snakeX == tailX[i] && snakeY == tailY[i]){
			gameover = true;
		}
	}
}

// ================= INPUT (TECLAS) =================
void input (){
	char tecla;
	
	if (kbhit()){ // si se presionó una tecla
		tecla = getch();
		
		// cambiar dirección (evitando reversa)
		if (tecla == 'a' && dir != right){
			dir = left;
		}
		else if (tecla == 'd' && dir != left){
			dir = right;
		}
		else if (tecla == 'w' && dir != down){
			dir = up;
		}
		else if (tecla == 's' && dir != up){
			dir = down;
		}
	}
}

// ================= DIBUJAR =================
void draw(){
	
	printf("Puntaje: %d\n", score);
	printf("Highscore: %d\n", highscore);
	
	// borde superior
	for (int i = 0; i < anchoTablero + 2; i++){
		printf("#");
	}
	printf("\n");
	
	// contenido del tablero
	for (int j = 0; j < altoTablero; j++){
		printf("#"); // borde izquierdo
		
		for (int i = 0; i < anchoTablero; i++){
			
			bool cola = false;
			
			// verificar si hay cola en esa posición
			for (int k = 0; k < snakeCola; k++){
				if(i == tailX[k] && j == tailY[k]){
					cola = true;
				}
			}
			
			// dibujar cabeza
			if (i == snakeX && j == snakeY){
				printf("0");
			}
			// dibujar cola
			else if (cola){
				printf("o");
			}
			// dibujar comida
			else if (i == foodX && j == foodY){
				printf("*");
			}
			// espacio vacío
			else{
				printf(" ");
			}
		}
		
		printf("#\n"); // borde derecho
	}
	
	// borde inferior
	for (int i = 0; i < anchoTablero + 2; i++){
		printf("#");
	}
	printf("\n");
}

// ================= MAIN =================
int main() {
	
	int opcion;
	
	srand(time(0));     // inicializa random
	cargarHighscore();  // carga el récord
	
	while (1){ // loop principal del juego
		
		// reinicio de variables
		score = 0;
		snakeCola = 0;
		gameover = false;
		velocidad = 200000;
		
		// posición inicial
		snakeX = anchoTablero / 2;
		snakeY = altoTablero / 2;
		
		// comida inicial
		foodX = rand() % anchoTablero;
		foodY = rand() % altoTablero;
		
		dir = right; // empieza moviéndose
		
		// ================= LOOP DEL JUEGO =================
		while (gameover == false){
			system("cls"); // limpiar pantalla
			
			input();   // leer teclas
			draw();    // dibujar
			logic();   // actualizar lógica
			
			usleep(velocidad); // control de velocidad
		}
		
		// ================= GAME OVER =================
		printf("\n==== GAME OVER ====\n");
		printf("Puntaje final: %d\n", score);
		printf("Highscore: %d\n", highscore);
		
		// guardar récord si se supera
		if (score > highscore){
			highscore = score;
			guardarHighscore();
		}
		
		// menú
		printf("\n1. Jugar otra vez\n");
		printf("2. Salir\n");
		scanf("%d", &opcion);
		
		if (opcion != 1){
			break;
		}
	}
	
	return 0;
}
