#include <stdio.h>

int main(void) {
    char c = 'A';
    signed char sc = -5;
    unsigned char uc = 200;

    short s = -1234;
    signed short ss = -1234;
    unsigned short us = 43210;

    int i = -42;
    signed int si = -42;
    unsigned int ui = 123456789;

    long int li = -987654321L;
    signed long int sli = -987654321L;
    unsigned long int uli = 9876543210UL;

    long long int lli = -1234567890123LL;
    signed long long int slli = -1234567890123LL;
    unsigned long long int ulli = 1234567890123ULL;

    float f = 3.75f;
    double d = 123.456;
    long double ld = 9876.54321L;

    printf("char = %c\n", c);
    printf("signed char = %d\n", sc);
    printf("unsigned char = %u\n", uc);

    printf("short = %hd\n", s);
    printf("signed short = %hd\n", ss);
    printf("unsigned short = %hu\n", us);

    printf("int = %d\n", i);
    printf("signed int = %d\n", si);
    printf("unsigned int = %u\n", ui);

    printf("long int = %ld\n", li);
    printf("signed long int = %ld\n", sli);
    printf("unsigned long int = %lu\n", uli);

    printf("long long int = %lld\n", lli);
    printf("signed long long int = %lld\n", slli);
    printf("unsigned long long int = %llu\n", ulli);

    printf("float = %.2f\n", f);
    printf("double = %.3f\n", d);
    printf("long double = %.5Lf\n", ld);

    return 0;
}
