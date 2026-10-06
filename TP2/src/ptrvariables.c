#include <stdio.h>
#include <stdint.h>

int main(void) {
    char c = 'A';
    short s = 12;
    int i = 42;
    long int li = 123456L;
    long long int lli = 9876543210LL;
    float f = 3.75f;
    double d = 12.5;
    long double ld = 123.456L;

    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long int *pli = &li;
    long long int *plli = &lli;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("Avant la manipulation :\n");
    printf("Adresse de c : %p, valeur de c : %d\n", (void *)pc, *pc);
    printf("Adresse de s : %p, valeur de s : %d\n", (void *)ps, *ps);
    printf("Adresse de i : %p, valeur de i : %d\n", (void *)pi, *pi);
    printf("Adresse de li : %p, valeur de li : %ld\n", (void *)pli, *pli);
    printf("Adresse de lli : %p, valeur de lli : %lld\n", (void *)plli, *plli);
    printf("Adresse de f : %p, valeur de f : %.2f\n", (void *)pf, *pf);
    printf("Adresse de d : %p, valeur de d : %.2f\n", (void *)pd, *pd);
    printf("Adresse de ld : %p, valeur de ld : %.2Lf\n\n", (void *)pld, *pld);

    *pc = 'Z';
    *ps = 30;
    *pi = 99;
    *pli = 654321L;
    *plli = 1234567890LL;
    *pf = 7.5f;
    *pd = 21.0;
    *pld = 456.789L;

    printf("Apres la manipulation :\n");
    printf("Adresse de c : %p, valeur de c : %d\n", (void *)pc, *pc);
    printf("Adresse de s : %p, valeur de s : %d\n", (void *)ps, *ps);
    printf("Adresse de i : %p, valeur de i : %d\n", (void *)pi, *pi);
    printf("Adresse de li : %p, valeur de li : %ld\n", (void *)pli, *pli);
    printf("Adresse de lli : %p, valeur de lli : %lld\n", (void *)plli, *plli);
    printf("Adresse de f : %p, valeur de f : %.2f\n", (void *)pf, *pf);
    printf("Adresse de d : %p, valeur de d : %.2f\n", (void *)pd, *pd);
    printf("Adresse de ld : %p, valeur de ld : %.2Lf\n", (void *)pld, *pld);

    return 0;
}
