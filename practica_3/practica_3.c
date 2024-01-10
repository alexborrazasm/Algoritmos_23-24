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

#define TAM 256000 
// Define el tamaño máximo del vector en el montículo

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo *pmonticulo;

void listar_vector(int v[], int n) {
    int i = 0;

    for (i = 0; i < n; i++)
        printf("%3d", v[i]);

    printf("\n");
}   // Imprime un vector

void hundir(pmonticulo m, int i) {
    int j, t, hijoIzq, hijoDer;

    do {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        j = i;
        if (hijoIzq <= m->ultimo && m->vector[hijoIzq] < m->vector[i])
            i = hijoIzq;
        if (hijoDer <= m->ultimo && m->vector[hijoDer] < m->vector[i])
            i = hijoDer;
        if (j != i) {
            t = m->vector[i];
            m->vector[i] = m->vector[j];
            m->vector[j] = t;
        }
    } while (j != i);
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    int i;

    for (i = 0; i < n; ++i) {
        m->vector[i] = v[i];
    }
    m->ultimo = n - 1;
    for (i = (n / 2) - 1; i >= 0; i--) {
        hundir(m, i);
    }
}   // Crea un montículo

int quitarMenor(pmonticulo m) {
    int x;

    if (m->ultimo == -1) {
        fprintf(stderr, "Error: Monticulo vacio\n");
        exit(EXIT_FAILURE);
    }
    else {
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo--;
        if (m->ultimo > 0) {
            hundir(m, 0);
        }
    }
    return x;
}

void ord_monticulo(int v[], int n, pmonticulo m) {
    int i;

    crearMonticulo(v, n, m);

    for (i = 0; i < n; i++) {
        v[i] = quitarMenor(m);
    }
}   // Algoritmo de ordenación por montículos

int ordenado(int v[], int n) {
    int i;

    for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1])
            return 0;
    }
    return 1;    
}   // Comprueba si un vector está ordenado

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++) {
        v[i] = (rand() % m) - n;
    } 
}   // Se generan números pseudoaleatorio entre -n y +n

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (i + 1);
    }
}   // Se generan números en orden ascendente

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (n - i);
    }    
}   // Se generan números en orden descendente

double microsegundos() { 
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);   
}   // Obtiene la hora del sistema en microsegundos

void inicializar_semilla() {
    srand(time(NULL));
    
}   // Se establece la semilla de una nueva serie de enteros pseudo-aleatorios

void testCrearMonticulo() {
    int v[10], n = 10;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    printf("Test crear monticulo:\n");
    printf("Inicializacion aleatoria:\n");
    aleatorio(v, n);
    listar_vector(v, n);
    crearMonticulo(v, n, m);
    printf("Vector del monticulo:\n");
    listar_vector(m->vector, 10);
    printf("_____________________________________________________\n");
    free(m);
    // Test del funcionamiento de crearMonticulo
}

void testAux(int v[],int n, void (*gen)(int v[], int n), 
             void (*alg)(int v[], int n, pmonticulo m)) {
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    gen(v, n);
    listar_vector(v, n);
    printf("Esta ordenado? %d\n", ordenado(v, n));
    alg(v, n, m);
    printf("Vector ordenado:\n");
    listar_vector(v, n);
    printf("Esta ordenado? %d\n", ordenado(v, n));
    printf("_____________________________________________________\n");
    free(m);
}

void testOrdMonticulo() {
    int v[17], n = 17;
    printf("Test ordenacion por montoculos:\n");
    printf("Inicializacion aleatoria:\n");
    testAux(v, n, aleatorio, ord_monticulo);
    printf("Inicializacion ascendente:\n");
    testAux(v, n, ascendente, ord_monticulo);
    printf("Inicializacion descendente:\n");
    testAux(v, n, descendente, ord_monticulo);
}   // Test del funcionamiento de ord_monticulo

double medirTiempos(void (*alg)(int v[], int n, pmonticulo m), 
                    void (*gen)(int v[], int n), int n) {
    double inicio = 0.0, fin = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
    int k = 1000, i; 
    int *v;
    v = malloc(n * sizeof(int));
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    gen(v, n);
    inicio = microsegundos();
    alg(v, n, m);
    fin = microsegundos();
    t = fin - inicio;
    if (t < 500) {
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++) {
            gen(v, n);
            alg(v, n, m);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++) {
            gen(v, n);
        }
        fin = microsegundos();
        t2 = fin - inicio;
        t = (t1 - t2) / k;
    }
    free(v);
    free(m);
    return t;
}

void analisisCrear(){
    int n;
    double tiempo;
    printf("\n Analisis creacion de monticulos:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n^0.8]______"
           "____[t(n)/n]______________[t(n)/n^1.2]___\n");
    for (n = 500; n <= 128000; n = n * 2) {
        tiempo = medirTiempos(crearMonticulo, aleatorio, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/pow(n,0.8),'|', tiempo/n,'|',
         tiempo/pow(n, 1.2));
    }
    printf("________________________________________________________________"
    "_____________________________________\n\n");
}

void analisisMonAscendente() {
    double tiempo = 0.0;
    int n;

    printf("Analisis ascendente:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n^1.07]_________[t(n)/n^1.3]___\n");                             
    for (n = 500;n <= 128000; n=n*2){
        tiempo=medirTiempos(ord_monticulo, ascendente, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/pow(n, 1.07),'|',
         tiempo/pow(n, 1.3));
    }
    printf("________________________________________________________________"
    "_____________________________________\n");
}

void analisisMonDescendente() {
    double tiempo = 0.0;
    int n;

    printf("Analisis descendente:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n^1.07]_________[t(n)/n^1.3]___\n");                             
    for (n = 500;n <= 128000; n=n*2){
        tiempo=medirTiempos(ord_monticulo, descendente, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/pow(n, 1.07),'|',
         tiempo/pow(n, 1.3));
    }
    printf("________________________________________________________________"
    "_____________________________________\n");
}

void analisisMonAleatorio() {
    double tiempo = 0.0;
    int n;

    printf("Analisis aleatorio:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n*logn]_________[t(n)/n^1.3]___\n");                          
    for (n = 500;n <= 128000; n=n*2){
        tiempo=medirTiempos(ord_monticulo, aleatorio, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/(n*log(n)),'|',
         tiempo/pow(n, 1.3));
    }
    printf("________________________________________________________________"
    "_____________________________________\n");
}

void analisisOrdMonticulos() {
    printf("Analisis ordenacion por monticulos:\n");
    analisisMonAscendente();
    analisisMonDescendente();
    analisisMonAleatorio();
    printf("\n");
}

int main() {
    inicializar_semilla();
    testCrearMonticulo();
    testOrdMonticulo();
    analisisCrear();
    analisisCrear();
    analisisCrear();
    analisisOrdMonticulos();
    analisisOrdMonticulos();
    analisisOrdMonticulos();
    return 0;
}