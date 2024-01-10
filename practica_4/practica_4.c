/*  Grupo:
    Alexandre Borrazás Mancebo : alexandre.bmancebo@udc.es
    Marco Gualillo Lago : marco.gualillo@udc.es
    Luis Mera Mujico : l.mera1@udc.es
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define TAM_MAX 1000
typedef int ** matriz;

void dijkstra(matriz grafo, matriz distancias, int tam) {
    int n, i, j, min, v = 0;
    for (n = 0; n < tam; n++) {
        int *noVisitados = malloc(tam * sizeof(int));
        for (i = 0; i < tam; i++) {
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        for (j = 0; j < tam - 2; j++) {
            min = TAM_MAX;
            for (i = 0; i < tam; i++) {
                if (noVisitados[i] && distancias[n][i] < min) {
                    min = distancias[n][i];
                    v = i;
                }
            }
            noVisitados[v] = 0;
            for (i = 0; i < tam; i++) {
                if (noVisitados[i] && distancias[n][i] > distancias[n][v] +
                   grafo[v][i]) {
                    distancias[n][i] = distancias[n][v] + grafo[v][i];
                }
            }
        }
        free(noVisitados);
    }
}

matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n * sizeof(int *))) == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;
    return aux;
}

matriz matrizTest1() {
    int m[5][5] = {{0, 1, 8, 4, 7},
                   {1, 0, 2, 6, 5},
                   {8, 2, 0, 9, 5},
                   {4, 6, 9, 0, 3},
                   {7, 5, 5, 3, 0}};
    matriz g = (matriz)malloc(5 * sizeof(int *));
    for (int i = 0; i < 5; i++){
        g[i] = (int *)malloc(5 * sizeof(int));
    }
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            g[i][j] = m[i][j];
        }
    }
    return g;
}

matriz matrizTest2() {
    int m[4][4] = {{0, 1, 4, 7},
                   {1, 0, 2, 8},
                   {4, 2, 0, 3},
                   {7, 8, 3, 0}};
    matriz g = (matriz)malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++){
        g[i] = (int *)malloc(4 * sizeof(int));
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            g[i][j] = m[i][j];
        }
    }
    return g;
}

/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
no dirigido con n nodos, representado por su matriz de adayencia */
void iniMatriz(matriz m, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberarMatriz(matriz m, int n) {
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void printMatriz(matriz m, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%4d",m[i][j]);
		}
        puts("");
	}
}

void printTabla(matriz m, int n){
    int i, j;
    printf("____");
    for (i = 0; i < n; i++) {
        printf("%4d", i);
    }
    puts("____");
    for(i = 0; i < n; i++){
        printf("%3d|", i);
		for(j = 0; j < n; j++){
			printf("%4d",m[i][j]);
		}
        puts("");
	}
}

void testAux(matriz grafo, int tam) {
    matriz distancias = crearMatriz(tam);
    printf("Matriz de adyacencia:\n");
    printMatriz(grafo, tam);
    dijkstra(grafo, distancias, tam);
    printf("Distancias mínimas:\n");
    printTabla(distancias, tam);
    liberarMatriz(distancias, tam);
}

void testGrafos() {
    printf("Test grafos:\n");
    matriz matriz1 = matrizTest1();
    matriz matriz2 = matrizTest2();
    matriz matrizA1 = crearMatriz(5);
    matriz matrizA2 = crearMatriz(5);
    testAux(matriz1, 5);
    liberarMatriz(matriz1, 5);
    printf("____________________________\n");
    testAux(matriz2, 4);
    liberarMatriz(matriz2, 4);
    printf("________________________\n");
    printf("Test aleatorio:\n");
    iniMatriz(matrizA1, 5);
    iniMatriz(matrizA2, 5);
    printf("Matriz aleatoria 1:\n");
    printMatriz(matrizA1, 5);
    printf("_____________________\n");
    printf("Matriz aleatoria 2:\n");
    printMatriz(matrizA2, 5);
    printf("_____________________\n");
    liberarMatriz(matrizA1, 5);
    liberarMatriz(matrizA2, 5);
}

double microsegundos() { 
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);   
}   // Obtiene la hora del sistema en microsegundos

void inicializar_semilla() {
    srand(time(NULL));
    
}   // Se establece la semilla de una nueva serie de enteros pseudo-aleatorios

double medirTiempos(void (*alg)(matriz grafo, matriz distancias, int n), 
                   void (*gen)(matriz m, int n), int n) {
    double inicio = 0.0, fin = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
    int k = 1000, i; 
    matriz grafo = crearMatriz(n);
    matriz distancias = crearMatriz(n);
    gen(grafo, n);
    inicio = microsegundos();
    alg(grafo, distancias, n);
    fin = microsegundos();
    t = fin - inicio;
    if (t < 500) {
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++) {
            gen(grafo, n);
            alg(grafo, distancias, n);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++) {
            gen(grafo, n);
        }
        fin = microsegundos();
        t2 = fin - inicio;
        t = (t1 - t2) / k;
    }
    liberarMatriz(grafo, n);
    liberarMatriz(distancias, n);
    return t;
}

void analisisGrafo() {
    double tiempo = 0.0;
    int n;

    printf("Analisis cálculo de las distancias mínimas:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n^2.6]______"
           "____[t(n)/n^2.84]_________[t(n)/n^3]_____\n");                             
    for (n = 5;n <= 1000; n=n*2){
        tiempo=medirTiempos(dijkstra, iniMatriz, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/pow(n, 2.6),'|', tiempo/pow(n, 2.84),'|',
         tiempo/pow(n, 3));
    }
    printf("________________________________________________________________"
    "_____________________________________\n");
}

int main() {
    inicializar_semilla();
    testGrafos();
    analisisGrafo();
    analisisGrafo();
    analisisGrafo();
    return 0;
}