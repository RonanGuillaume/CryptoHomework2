#ifndef PROJECT_EXERCISE2_2B_H
#define PROJECT_EXERCISE2_2B_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

void poly8_bitSlice_b(poly8x64 r, const poly8 *x);
void poly8x64_sqrtMod_b(poly8x64 r, const poly8x64 a);
void poly8x64_unBitSlice_b(poly8 *r, const poly8x64 x);
static void poly8mod_print_b(const poly8 x);
int main_2b();

#endif //PROJECT_EXERCISE2_2B_H
