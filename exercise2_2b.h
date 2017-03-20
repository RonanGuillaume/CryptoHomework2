#ifndef PROJECT_EXERCISE2_2B_H
#define PROJECT_EXERCISE2_2B_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

unsigned long long ull_mul_2b(unsigned long long a);
void poly8x64_mulmod_2b(poly8x64 r, const poly8x64 a, const poly8x64 b);
static void poly8mod_print(const poly8 x);
int main_2b();

#endif //PROJECT_EXERCISE2_2B_H
