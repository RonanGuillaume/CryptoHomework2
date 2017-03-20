#ifndef PROJECT_EXERCISE2_2A_H
#define PROJECT_EXERCISE2_2A_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

void print1(unsigned char a);
void print2(unsigned long long a);
void poly8_bitslice(poly8x64 r, const poly8 x[64]);
int poly_degree(unsigned long long a);
unsigned long long ull_mul(unsigned long long a, unsigned long long b);
void poly8x64_mulmod(poly8x64 r, const poly8x64 a, const poly8x64 b);
void poly8x64_unbitslice(poly8 r[64], const poly8x64 x);
static void poly8mod_print(const poly8 x);
int main_2a();

#endif //PROJECT_EXERCISE2_2A_H
