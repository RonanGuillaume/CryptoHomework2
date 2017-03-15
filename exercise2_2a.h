#ifndef PROJECT_EXERCISE2_2A_H
#define PROJECT_EXERCISE2_2A_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

void poly8_bitSlice(poly8x64 r, const poly8 x[64]);
void poly8x64_mulMod(poly8x64 r, const poly8x64 a, const poly8x64 b);
void poly8x64_unBitSlice(poly8 *r, const poly8x64 x);
static void poly8mod_print(const poly8 x);
int main_2a();

#endif //PROJECT_EXERCISE2_2A_H
