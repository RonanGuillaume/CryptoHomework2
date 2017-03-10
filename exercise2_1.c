#include "exercise2_1.h"

uint32_t modExp(uint32_t a, unsigned char *e) {
    int i,j;
    uint32_t r = 1;
    for(i=3;i>=0;i--) {
        for(j=7;j>=0;j--) {
            r = r*r;
            if(e[i] & (1<<j))
                r = a*r;
        }
    }
    return r;
}

uint32_t modExp_V2(uint32_t a, unsigned char *e){
    int i,j;
    uint32_t r = 1;

    //todo

    return r;
}



/* Pipe output through sage */
int main_1(void){
    FILE *urandom = fopen("/dev/urandom", "r");
    uint32_t a,r,ei;
    unsigned char e[4];
    int i,j;

    for(i=0;i<N_TESTS;i++) {
            fread(&a,sizeof(uint32_t),1,urandom);
            fread(e,sizeof(unsigned char),4,urandom);

//        a = 3;
//        e[0] = 3;
//        e[1] = 0;
//        e[2] = 0;
//        e[3] = 0;

        //r=(a^ei)%(2^32)
        //          ----
        //because r is an int on 32bit
        r = modExp(a, e);

        /*
        * e is a table where each cells contains a number between 0 and 255,
        * ei = e[0]*256^0 + e[1]*256^1 + e[2]*256^2 + e[3]*256^3
        */
        ei = 0;
        for(j=0;j<4;j++)
            ei |= (uint32_t)e[j] << 8*j;

        printf("power_mod(%u,%u,2^32) - %u\n", a,ei,r);
    }

    fclose(urandom);
    return 0;
}
