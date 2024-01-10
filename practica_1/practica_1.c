/*  Alexandre Borrazás Mancebo : alexandre.bmancebo@udc.es
    Marco Gualillo Lago : marco.gualillo@udc.es
    Luis Mera Mujico : l.mera1@udc.es
    Nota 9.5
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<math.h>

int sumaSubMax1(int v[], int n) {
    int sumaMax = 0, estaSuma, i,j;

    for (i = 0; i < n; i++) {
        estaSuma = 0;
        for (j = i; j < n; j++) {
            estaSuma = estaSuma + v[j];
            if (estaSuma > sumaMax)
                sumaMax = estaSuma;
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[], int n) {
    int j, estaSuma = 0, sumaMax = 0;

    for (j = 0; j < n; j++) {
        estaSuma = estaSuma + v[j];
        if (estaSuma > sumaMax)
            sumaMax = estaSuma;
        else if (estaSuma < 0)
            estaSuma = 0;
    }
    return sumaMax;
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v [], int n) {
    int i, m = 2 * n + 1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

double medirTiempos(int  suma (int v[], int n), int n) {
    double inicio = 0.0, fin = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
    int k = 1000, *v, i;
    
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

void listar_vector (int v[], int n) {
    int i = 0;
    for(i = 0; i < n; i++)
        printf("%3d", v[i]);
}

void inicializar_semilla() {
    srand(time(NULL));
    /* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void test1(){
    int v[6][5] =    {{-9,2,-5,-4,6},{4,0,9,2,5},{-2,-1,-9,-7,-1},
                    {9,-2,1,-7,-8},{15,-2,-5,-4,16},{7,-5,6,7,-7}};
                     
    int i;
    printf("test 1:\n");
    printf("%16s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i= 0;i < 6; i++){
        listar_vector(v[i],5);
        printf("\t\t");
        printf("%2d\t\t", sumaSubMax1(v[i],5));
        printf("%2d\n", sumaSubMax2(v[i],5));
    }
    printf("\n");
}

void test2() {
    int i, a, b;
    int v[9];

    printf("test 2:\n");
    printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i = 0; i<10; i++) {
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}

void analisisSuma1() {
    double tiempo = 0.0;
    int n;
    
    printf("Algoritmo SumaSubMax 1:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^1.8]________"
           "____[t(n)/n^2.0]_________[t(n)/n^2.2]___\n");
    for (n = 500; n <= 32000; n=n*2){
        tiempo=medirTiempos(sumaSubMax1, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,1.8)),'|', tiempo/(pow(n,2)),'|',
         tiempo/(pow(n,2.2)));
    }
}

void analisisSuma2() {
    double tiempo = 0.0;
    int n;

    printf("Algoritmo SumaSubMax 2:\n");
    printf("____________[N]__________[t(n)]_________[t(n)/n^0.8]________"
           "______[t(n)/n]___________[t(n)/n^1.2]___\n");
    for (n = 500; n <= 256000; n=n*2){
        tiempo = medirTiempos(sumaSubMax2, n);
        printf("\t%7d%4c%14.3f%4c%18.12f%4c%18.12f%4c%18.12f\n",
        n,'|', tiempo,'|', tiempo/(pow(n,0.8)),'|', tiempo/n,'|', 
        tiempo/(pow(n,1.2)));
    }
}

int main() {
    inicializar_semilla();
    test1();
    test2();
    analisisSuma1();
    analisisSuma1();
    analisisSuma1();
    analisisSuma2();
    analisisSuma2();
    analisisSuma2();

    return 0;
}