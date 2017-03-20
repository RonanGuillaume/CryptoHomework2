#include <stdio.h>
#include "exercise2_2a.h"
#include "exercise2_2b.h"

typedef unsigned char poly8;
typedef unsigned long long poly8x64[8];

unsigned long long ull_mul_2b(unsigned long long a)
{
    unsigned long long reduction = 0x0000000000000040LL;
    unsigned long long sol = 0, tmp = 0;
    int n, red_degree = poly_degree(reduction);

    for (n = 0; n < 64; n++) {
        if ((a >> n) & 1) {
            sol ^= a << n;

            if (n == red_degree) {
                sol ^= (1 << n) ^ reduction;
            }
        }
    }
    return sol;
}


/* reduction polynomial x^8 + x^4 + x^3 + x + 1 */
void poly8x64_mulmod_2b(poly8x64 r, const poly8x64 a, const poly8x64 b)
{
    unsigned long long poly_tmp;
    unsigned long long reduction = 0x000000000000011BLL;
    int i, n, red_degree = poly_degree(reduction);

    for (i = 0; i < 8; i++) {

        poly_tmp = 0;
        for (n = 0; n < 64; n++) {
            if ((a[i] >> n) & 1) {
                poly_tmp ^= a[i] << n;

                if (n == red_degree) {
                    poly_tmp ^= (1 << n) ^ reduction;
                }
        }
    }
        r[i] = poly_tmp;
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
int main_2b()
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

/*  unsigned long long bla1 = 0x000000000000000CLL;
  print2(bla1);
  print2(ull_mul(bla1));
  return 0;*/

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