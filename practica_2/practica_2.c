/*  Grupo:
    Alexandre Borrazás Mancebo : alexandre.bmancebo@udc.es
    Marco Gualillo Lago : marco.gualillo@udc.es
    Luis Mera Mujico : l.mera1@udc.es
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

bool ordenado(int v[], int n) {  // Comprueba si un vector está o no ordenado menor a mayor
    int i;
    for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i+1])
            return false;
    }
    return true;
}

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
    /* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void ord_ins (int v[], int n) {  // Algoritmo de ordenación por inserción
    int i, x, j; 
    for (i = 1; i < n; i++){
        x = v[i];
        j = i-1;
        while (j > -1 && v[j] > x){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}

void ord_shell (int v[], int n) {    // Algoritmo de ordenación shell
    int incremento = n;
    int i, tmp, j;
    bool seguir;
    do{
        incremento = incremento / 2;
        for (i = incremento; i < n; i++){
            tmp = v[i];
            j = i;
            seguir = true;
            while (j - incremento > -1 && seguir){
                if (tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                } else {
                    seguir = false;
                }
            }
            v[j] = tmp;
        }
    } while (incremento != 1);
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
    testAux("Insercin", ord_ins);
    testAux("Shell", ord_shell);
}

void analisis_aleatorio(){
    double tiempo = 0.0;
    int n;

    printf("\nOrdenacion por insercion con inicializacion aleatoria:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.8]________"
           "____[t(n)/n^2.0]_________[t(n)/n^2.2]___\n");                               
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medirTiempos(ord_ins, n, aleatorio);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.8)),'|', tiempo/(pow(n,2)),'|',
         tiempo/(pow(n,2.2)));
    }
    printf("\nOrdenacion por shell con inicializacion aleatoria:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.1]________"
           "____[t(n)/n^1.19]________[t(n)/n^1.3]___\n");
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medirTiempos(ord_shell, n, aleatorio);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.1)),'|', tiempo/(pow(n,1.19)),'|',
         tiempo/(pow(n,1.3)));
    }
    puts("");
}

void analisis_ascendente() {
    double tiempo = 0.0;
    int n;
    
    printf("\nOrdenacion por insercion con inicializacion ascendente:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^0.8]________"
           "______[t(n)/n]___________[t(n)/n^1.2]___\n");                     
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medirTiempos(ord_ins, n, ascendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,0.8)),'|', tiempo/n,'|', 
        tiempo/(pow(n,1.2)));
    }
    printf("\nOrdenacion por shell con inicializacion ascendente:\n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n^1.14]________[t(n)/n^1.3]___\n");                                
    for (n = 500;n <= 32000; n=n*2) {
        tiempo=medirTiempos(ord_shell, n, ascendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/(pow(n,1.14)),'|', 
        tiempo/(pow(n,1.3)));
    }
    puts("");
}

void analisis_descendente() {
    double tiempo = 0.0;
    int n;
    
    printf("\nOrdenacion por insercion con inicializacion descendente:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.8]________"
           "____[t(n)/n^2.0]_________[t(n)/n^2.2]___\n");                              
    for (n = 500;n <= 32000; n=n*2) {
        tiempo=medirTiempos(ord_ins, n, descendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.8)),'|', tiempo/(pow(n,2)),'|',
        tiempo/(pow(n,2.2)));
    }
    printf("\nOrdenacion por shell con inicializacion descendente: \n");
    printf("____________[N]__________[t(n)]___________[t(n)/n]__________"
           "____[t(n)/n^1.14]________[t(n)/n^1.3]___\n");                        
    for (n = 500;n <= 32000; n=n*2) {
        tiempo=medirTiempos(ord_shell, n, descendente);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/n,'|', tiempo/(pow(n,1.14)),'|', 
        tiempo/(pow(n,1.3)));
    }
    puts("");
}

void analisis() {
    analisis_aleatorio();
    analisis_ascendente();
    analisis_descendente();
}

int main() {
    inicializar_semilla();
    test();
    analisis();
    analisis();
    analisis();
    return 0;
}