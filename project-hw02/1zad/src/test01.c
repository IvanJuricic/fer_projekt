#include <cmplx.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    cmplx_t a,b,c;
    a[0] = 2;
    a[1] = 2;
    b[0] = 1;
    b[1] = 2;
    cmplx_div(a,b,c);
    if(c[0]!=(6/5) && c[1]!=(-2/5)){
        printf("Test neuspjesan!");
        return -1;
    }
    else printf("Test uspjesan!");
    return 0;
}