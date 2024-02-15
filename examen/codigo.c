/* Examén de prácticas Algoritmos: Fecha = 18/01/2024
Autor: Alexandre Borrazás Mancebo -> alexandre.bmancebo@udc.es
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<sys/time.h>
#include<math.h>

void printV(int array[], int n) {  // Imprime un vector
    int i;
    for (i = 0; i < n; i++) {
        if (i == 0) {
            printf("[%d, ", array[i]);
        } else if (i < n-1) {
            printf("%d, ", array[i]);
        } else {
            printf("%d]\n", array[i]);
        }
    }
}

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* Se rellena un vector con números pseudoaleatorio entre -n y +n */
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (i + 1);
    }
    /* Se rellena un vector con números en orden ascendente */
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (n - i);
    }
    /* Se rellena un vector con números en orden descendente */
}

bool ordenado(int v[], int n) {  
    int i;
    for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i+1])
            return false;
    }
    return true;
} // Comprueba si un vector está o no ordenado menor a mayor

double microsegundos() { // Obtiene la hora del sistema en microsegundos
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double medirTiempos(void alg(int v[], int n), int n, 
                    void gen(int v[], int n)) {
    double inicio = 0.0, fin = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
    int k = 1000, *v, i;
    
    v = malloc(n*sizeof(int));
    gen(v,n);
    inicio = microsegundos();
    alg(v,n);
    fin = microsegundos();
    t=fin-inicio;
    if (t<500){
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           gen(v,n);
           alg(v,n);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           gen(v,n);
        }
        fin = microsegundos();
        t2 = fin - inicio;
        t = (t1 - t2)/k;
    }
    free(v);
    return t;
}

void inicializar_semilla() {
    srand(time(NULL));
    /* se establece la semilla de una nueva serie 
    de enteros pseudo-aleatorios */
}

void intercambiar(int *e1, int *e2) {
    int temp;
    temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

void auxOrd(int v[], int izq, int der) {
    int piv, i, j;

    if (izq < der) {
        piv = v[der - 1];
        intercambiar(&v[izq], &v[der - 1]);
        i = izq + 1;
        j = der;

        while (i <= j) {
            while (v[j] > piv) {
                j--;    
            }
            while (i <= der && v[i] < piv) {
                i++;
            }
            if (i <= j) {
                intercambiar(&v[i], &v[j]);
                i++;
                j--;
            }
        }
        // Deshacer el último intercambio
        intercambiar(&v[izq], &v[j]);
        // Llamadas recursivas
        auxOrd(v, izq, j-1);
        auxOrd(v, j+1, der);
    } 
} // Implementación de QuickSort

void ordenar (int v[], int n) {
    auxOrd(v, 0, n-1);
}

void testAux(char *nombre, void ord(int v[], int n)) {
    int v[17];
    printf("\nTest %s:\n", nombre);
    // Test vector aleatorio
    aleatorio(v, 17);
    printf("Inicializacion aleatoria:\n");
    printV(v, 17);
    printf("ordenado? %s\n", ordenado(v, 17)? "Si" : "No");
    printf("Ordenacion por %s\n", nombre);
    ord(v, 17);
    printV(v, 17);
    printf("ordenado? %s\n\n", ordenado(v, 17)? "Si" : "No");
    // Test vector descendente
    descendente(v, 10);
    printf("Inicializacion descendente:\n");
    printV(v, 10);
    printf("ordenado? %s\n", ordenado(v, 10)? "Si" : "No");
    printf("Ordenacion por %s\n", nombre);
    ord(v, 10);
    printV(v, 10);
    printf("ordenado? %s\n\n", ordenado(v, 10)? "Si" : "No");
    // Test vector ascendente
    ascendente(v, 10);
    printf("Inicializacion ascendente:\n");
    printV(v, 10);
    printf("ordenado? %s\n", ordenado(v, 10)? "Si" : "No");
    printf("Ordenacion por %s:\n", nombre);
    ord(v, 10);
    printV(v, 10);
    printf("ordenado? %s\n", ordenado(v, 10)? "Si" : "No");
    printf("-----------------------------------------------------\n\n");
}

void test() {
    testAux("Qsort", ordenar);
}

void analisis_aleatorio(){
    double tiempo = 0.0;
    int n;

    printf("\nOrdenacion por quicksort con inicializacion aleatoria:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n^1.11]________[t(n)/n^1.3]___\n");                             
    for (n = 500;n <= 64000; n=n*2){
        tiempo=medirTiempos(ordenar, n, aleatorio);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/(pow(n,1.11)),'|', 
        tiempo/(pow(n,1.3)));
    }
    puts("");
}

void analisis_ascendente() {
    double tiempo = 0.0;
    int n;
    
    printf("\nOrdenacion por quicksort con inicializacion ascendente:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.8]________"
           "____[t(n)/n^2.0]_________[t(n)/n^2.2]___\n");                     
    for (n = 500;n <= 64000; n=n*2){
        tiempo=medirTiempos(ordenar, n, ascendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.8)),'|', tiempo/(pow(n,2)),'|',
        tiempo/(pow(n,2.2)));
    }
    puts("");
}

void analisis_descendente() {
    double tiempo = 0.0;
    int n;
    
    printf("\nOrdenacion por quicksort con inicializacion descendente:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.8]________"
           "____[t(n)/n^2.0]_________[t(n)/n^2.2]___\n");                              
    for (n = 500;n <= 64000; n=n*2) {
        tiempo=medirTiempos(ordenar, n, descendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.8)),'|', tiempo/(pow(n,2)),'|',
        tiempo/(pow(n,2.2)));
    }
    puts("");
}

void analisis() {
    analisis_ascendente();
    analisis_descendente();
    analisis_aleatorio();
}


int main() {
    inicializar_semilla();
    test();
    analisis();
    analisis();
    analisis();

    return 0;
}