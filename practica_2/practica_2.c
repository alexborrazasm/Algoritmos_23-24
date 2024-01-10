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

void listar_vector (int v[], int n) {  // Imprime un vector
    int i = 0;
    for(i = 0; i < n; i++)
        printf("%3d", v[i]);
    printf("\n");
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (i + 1);
    }
    /* se generan números en orden descendente */
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (n - i);
    }
    /* se generan números en orden descendente */
}

int ordenado(int v[], int n) {  // Comprueba si un vector está o no ordenado
    int i;
    for (i = 0; i<n; i++) {
        if (v[i] > v[i+1])
            return 0;
    }
    return 1;
}

double microsegundos() { // Obtiene la hora del sistema en microsegundos
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double medir_aleatorio (void  suma (int v[], int n), int n) {
    double inicio = 0.0;
    double fin = 0.0;
    double t = 0.0;
    double t1 = 0.0;
    double t2 = 0.0;
    int k = 1000;
    int *v;
    int i;
    
    v = malloc(n*sizeof(int));
    aleatorio(v,n);
    inicio = microsegundos();
    suma(v,n);
    fin = microsegundos();
    t=fin-inicio;
    if (t<500){
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           aleatorio(v,n);
           suma(v,n);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           aleatorio(v,n);
        }
        fin = microsegundos();
        t2 = fin - inicio;
        t = (t1 - t2)/k;
    }
    free(v);
    return t;
}

double medir_ascendente (void  suma (int v[], int n), int n) {
    double inicio = 0.0;
    double fin = 0.0;
    double t = 0.0;
    double t1 = 0.0;
    double t2 = 0.0;
    int k = 1000;
    int *v;
    int i;
    
    v = malloc(n*sizeof(int));
    ascendente(v,n);
    inicio = microsegundos();
    suma(v,n);
    fin = microsegundos();
    t=fin-inicio;
    if (t<500){
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           ascendente(v,n);
           suma(v,n);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           ascendente(v,n);
        }
        fin = microsegundos();
        t2 = fin - inicio;
        t = (t1 - t2)/k;
    }
    free(v);
    return t;
}

double medir_descendente (void  suma (int v[], int n), int n) {
    double inicio = 0.0;
    double fin = 0.0;
    double t = 0.0;
    double t1 = 0.0;
    double t2 = 0.0;
    int k = 1000;
    int *v;
    int i;
    
    v = malloc(n*sizeof(int));
    descendente(v,n);
    inicio = microsegundos();
    suma(v,n);
    fin = microsegundos();
    t=fin-inicio;
    if (t<500){
        printf("(*)");
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           descendente(v,n);
           suma(v,n);
        }
        fin = microsegundos();
        t1 = fin - inicio;
        inicio = microsegundos();
        for (i = 0; i < k; i++){
           descendente(v,n);
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

void ord_ins (int v[], int n){  // Algoritmo de ordenación por inserción
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

void ord_shell (int v[], int n){    // Algoritmo de ordenación shell
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

void test_ins() {    // Test de ord_ins
    int v[17];
    printf("Test insercion:\n");
    aleatorio(v, 17);
    printf("Inicializacion aleatoria\n");
    listar_vector(v, 17);
    printf("ordenado? 0\n");
    printf("Ordenacion por insercion\n");
    ord_ins(v, 17);
    listar_vector(v, 17);
    printf("ordenado? 1\n");
    printf("\n");
    aleatorio(v, 10);
    descendente(v, 10);
    printf("Inicializacion descendente\n");
    listar_vector(v, 10);
    printf("ordenado? 0\n");
    printf("Ordenacion por insercion\n");
    ord_ins(v, 10);
    listar_vector(v, 10);
    printf("ordenado? 1\n");
    printf("\n");
    aleatorio(v, 10);
    ascendente(v, 10);
    printf("Inicializacion ascendente\n");
    listar_vector(v, 10);
    printf("ordenado? 0\n");
    printf("Ordenacion por insercion\n");
    ord_ins(v, 10);
    listar_vector(v, 10);
    printf("ordenado? 1\n");
    printf("-----------------------------------------------------\n");
}

void test_shell(){  // Test de ord_shell
    int v[17];
    printf("Test shell:\n");
    aleatorio(v, 17);
    printf("Inicializacion aleatoria\n");
    listar_vector(v, 17);
    printf("ordenado? 0\n");
    printf("Ordenacion por shell\n");
    ord_shell(v, 17);
    listar_vector(v, 17);
    printf("ordenado? 1\n");
    printf("\n");
    aleatorio(v, 10);
    descendente(v, 10);
    printf("Inicializacion descendente\n");
    listar_vector(v, 10);
    printf("ordenado? 0\n");
    printf("Ordenacion por shell\n");
    ord_shell(v, 10);
    listar_vector(v, 10);
    printf("ordenado? 1\n");
    printf("\n");
    aleatorio(v, 10);
    ascendente(v, 10);
    printf("Inicializacion ascendente\n");
    listar_vector(v, 10);
    printf("ordenado? 0\n");
    printf("Ordenacion por shell\n");
    ord_shell(v, 10);
    listar_vector(v, 10);
    printf("ordenado? 1\n");
    printf("-----------------------------------------------------\n");
}

void analisis_aleatorio(){
    double tiempo = 0.0;
    int n;

    printf("Ordenación por inserción con inicialización aleatoria: \n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n^1.8\t\t"     
            " t(n)/n^2.0\t\t     t(n)/n^2.2\n");                                
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_aleatorio(ord_ins,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n,tiempo, tiempo/(pow(n,1.8)), tiempo/(pow(n,2)), tiempo/(pow(n,2.2)));
    }
    printf("Ordenación por shell con inicialización aleatoria: \n");            
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n^1.1\t\t"     
            " t(n)/n^1.19\t\t     t(n)/n^1.3\n");
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_aleatorio(ord_shell,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n,tiempo, tiempo/(pow(n,1.1)), tiempo/((pow(n,1.19))), tiempo/(pow(n,1.3)));
    }
}

void analisis_ascendente(){
    double tiempo = 0.0;
    int n;
    
    printf("Ordenación por inserción con inicialización ascendente: \n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n^0.8\t\t"     
            " t(n)/n\t\t\t     t(n)/n^1.2\n");                         
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_ascendente(ord_ins,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n, tiempo, tiempo/(pow(n,0.8)), tiempo/n, tiempo/(pow(n,1.2))); 
    }
    printf("Ordenación por shell con inicialización ascendente: \n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n\t\t"     
            " t(n)/n^1.14\t\t     t(n)/n^1.3\n");                              
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_ascendente(ord_shell,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",   // revisar
        n,tiempo, tiempo/n, tiempo/(pow(n,1.14)), tiempo/(pow(n,1.3)));
    }
}

void analisis_descendente(){
    double tiempo = 0.0;
    int n;
    
    printf("Ordenación por inserción con inicialización descendente: \n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n^1.8\t\t"     
            " t(n)/n^2.0\t\t     t(n)/n^2.2\n");                                
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_descendente(ord_ins,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n,tiempo, tiempo/(pow(n,1.8)), tiempo/(pow(n,2)), tiempo/(pow(n,2.2))); 
    }
    printf("Ordenación por shell con inicialización descendente: \n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/n\t\t"     
            " t(n)/n^1.14\t\t     t(n)/n^1.3\n");                             
    for (n = 500;n <= 32000; n=n*2){
        tiempo=medir_descendente(ord_shell,n);
        printf("\t% 8d\t\t% 14.5f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n,tiempo, tiempo/n, tiempo/(pow(n,1.14)), tiempo/(pow(n,1.3)));
    }
}

int main() {
    inicializar_semilla();
    test_ins();
    test_shell();
    analisis_aleatorio();
    analisis_aleatorio();
    analisis_aleatorio();
    analisis_ascendente();
    analisis_ascendente();
    analisis_ascendente();
    analisis_descendente();
    analisis_descendente();
    analisis_descendente();
    return 0;
}