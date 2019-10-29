#include <cmplx.h>
#include <stdio.h>
int main()
{
    cmplx_t a;
    a[0]=2;
    a[1]=2;
    if(cmplx_mag(a)!=2){
        printf("Test 3 neuspjesan!\n");
        return 0;
    }

    printf("Test 3 uspjesan!\n");

    return 0;
}