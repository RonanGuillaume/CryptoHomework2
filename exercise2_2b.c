#include "exercise2_2b.h"

//todo
/*
 * instead of multiplication performs squaring.
 * Can we reduce the number of bit-logical operations (AND, XOR,. . . )
 * used by squaring compared to multiplication?
 */

void poly8_bitSlice_b(poly8x64 r, const poly8 *x)
{
    //TODO
}

/* reduction polynomial x^8 + x^4 + x^3 + x + 1 */
void poly8x64_mulMod_b(poly8x64 r, const poly8x64 a, const poly8x64 b)
{
    //TODO
}


void poly8x64_unBitSlice_b(poly8 *r, const poly8x64 x)
{
    //TODO
}



static void poly8mod_print_b(const poly8 x)
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
int main_2b()
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

    poly8_bitSlice_b(va, a);
    poly8_bitSlice_b(vb, b);

    printf("K.<a> = GF(2**8, name='a', modulus=x^8 + x^4 + x^3 +x + 1)\n");

    poly8x64_mulMod_b(vt, va, vb);
    poly8x64_unBitSlice_b(r, vt);

    for(i=0;i<64;i++)
    {
        poly8mod_print_b(a[i]);
        printf(" * ");
        poly8mod_print_b(b[i]);
        printf(" - ");
        poly8mod_print_b(r[i]);
        printf("\n");
    }

    fclose(urandom);
    return 0;
}