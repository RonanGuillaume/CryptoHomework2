#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

void print1(unsigned char a)
{
  int i;
  for (i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  //printf("\n");
}

void print2(unsigned long long a)
{
  int i;
  for (i = 0; i < 64; i++) {
      printf("%d", !!((a << i) & 0x8000000000000000));
  }
  //printf("\n");
}

void poly8_bitslice(poly8x64 r, const poly8 x[64])
{
    // Consider each byte array as an array of 64 binary polynomials.
    // r[i] is a long long (64 bytes)
    int i, n;
    unsigned char bit;
    for (n = 0; n < 8; n++) {
        unsigned long long bucket = 0;
        for(i = 0; i < 64; i++) {
            // take the nth bit of a polynomial
            bit = (x[i] >> n) & 1; //(x[i] & (1 << n)) >> n;
            bucket |= bit;
            if (i != 63) bucket <<= 1;
        }
        r[n] = bucket;
    }
    // Now, r[i] contains i-th factors of all polynomials (64 of them)
}


void poly8x64_unbitslice(poly8 r[64], const poly8x64 x)
{
    int i, j, n;
    unsigned char bit;
    for (i = 7; i >= 0; i--) {
        for (n = 0; n < 64; n++) {
            if (i == 7) {
              r[63-n] = 0;
            }
            // take the nth bit of a polynomial and put it in r[n]
            bit = (x[i] >> n) & 1;
            r[63-n] |= bit;
            if (i != 0) r[63-n] <<= 1;
        }
      }
}


unsigned long long ull_mul(unsigned long long a, unsigned long long b)
{
    unsigned long long sol = 0;
    int n;

    for (n = 0; n < 64; n++) {
        if ((b >> n) & 1) {
            sol |= a << n;
        }
    }
    return sol;
}


unsigned long long ull_red(unsigned long long a)
{
    // x8 + x4 + x3 + x + 1
    unsigned long long reduction = 0x000000000000011BLL;
    // if deg(poly) < deg(reduction), nothing happens
    // if deg(poly) == deg(reduction), remove most significant bit
    // if deg(poly) > deg(reduction), reduce


}

/* reduction polynomial x^8 + x^4 + x^3 + x + 1 */
void poly8x64_mulmod(poly8x64 r, const poly8x64 a, const poly8x64 b)
{
    int i;
    unsigned long long poly_tmp;

    for (i = 0; i < 8; i++) {
        poly_tmp = ull_mul(a[i], b[i]);
        //print2(poly_tmp); printf("\n");
    }
}


static void poly8mod_print(const poly8 x)
{
  int i;
  int d = 0;
  printf("K(");
  for (i = 0; i < 8; i++)
    if (1 & (x>>i))
    {
      if(d) printf(" + ");
      printf("a^%d",i);
      d = 1;
    }

  if (d == 0) printf("1");
  printf(")");
}


/* Pipe output through sage */
int main()
{

  poly8 a[64], b[64], r[64];
  poly8x64 va, vb, vt;
  int i;

  FILE *urandom = fopen("/dev/urandom","r");
  for(i=0;i<64;i++)
  {
    a[i] = fgetc(urandom);
    b[i] = fgetc(urandom);
  }

  poly8_bitslice(va, a);
  poly8_bitslice(vb, b);

  printf("K.<a> = GF(2**8, name='a', modulus=x^8 + x^4 + x^3 +x + 1)\n");

  poly8x64_mulmod(vt, va, vb);
  poly8x64_unbitslice(r, vt);

  for(i = 0; i < 64; i++) {
      poly8mod_print(a[i]);
      printf(" * ");
      poly8mod_print(b[i]);
      printf(" - ");
      poly8mod_print(r[i]);
      printf("\n");
  }
  
  fclose(urandom);
  return 0;
}