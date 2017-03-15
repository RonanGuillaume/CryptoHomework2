#include "exercise2_2a.h"


void poly8_bitSlice(poly8x64 r, const poly8 x[64])
{
    for (int i = 0; i < 8; i++) {
        r[i] = x[i*8];
        for (int j = 1; j < 8; j++) {
            r[i] = r[i]<<8;
            r[i] += x[i*8+j];
        }
    }
}

/* reduction polynomial x^8 + x^4 + x^3 + x + 1 */
void poly8x64_mulMod(poly8x64 r, const poly8x64 a, const poly8x64 b)
{
    for (int i = 7; i >= 0; i--){
        r[i] = (a[i]*b[i])%283;
    }
}


void poly8x64_unBitSlice(poly8 *r, const poly8x64 x)
{
    unsigned long long tmp;
    for (int i = 0; i < 8; ++i) {
        tmp = x[i];
        for (int j = 7; j >= 0; j--) {
            r[i*8+j] = (poly8)(tmp%256);
            tmp = tmp>>8;
        }
    }
}



static void poly8mod_print(const poly8 x)
{
  int i;
  int d=0;
  printf("K(");
  for(i=0;i<8;i++)
    if(1&(x>>i))
    {
      if(d) printf(" + ");
      printf("a^%d",i);
      d = 1;
    }
  if(d==0) printf("1");
  printf(")");
}


/* Pipe output through sage */
int main_2a()
{

  poly8 a[64], b[64], r[64];
  poly8x64 va, vb, vt;
  int i;

  FILE *urandom = fopen("/dev/urandom","r");
  for(i=0;i<64;i++)
  {
    a[i] = (poly8) fgetc(urandom);
    b[i] = (poly8) fgetc(urandom);
  }

    poly8_bitSlice(va, a);
    poly8_bitSlice(vb, b);

  printf("K.<a> = GF(2**8, name='a', modulus=x^8 + x^4 + x^3 +x + 1)\n");

    poly8x64_mulMod(vt, va, vb);
    poly8x64_unBitSlice(r, vt);

  for(i=0;i<64;i++)
  {
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
