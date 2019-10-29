#include <math.h>
#include <cmplx.h>

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c){
    c[0] = (a[0]*b[0]+a[0]*(-1)*b[1])/(b[0]*b[0]+b[1]*b[1]);
    c[1] = (a[0]*b[1]*(-1)+a[1]*b[0])/(b[0]*b[0]+b[1]*b[1]);
}

void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c){

}

double cmplx_mag(cmplx_t a){
    return sqrt((a[0]*a[0] + a[1]*a[1]));
}

double cmplx_phs(cmplx_t a){

}

double cmplx_real(double mag, double phs){

}

double cmplx_imag(double mag, double phs){

}

void cmplx_dft(cmplx_t *input, cmplx_t *output, int N){

}

void cmplx_idft(cmplx_t *input, cmplx_t *output, int N){

}