#include"donut.h"

float torusEquationX(float theta) {
    float R1 = 5.0;
    float R2 = 10.0;
    return R2 + R1 * cos(theta);
}

float torusEquationY(float theta) {
    float R1 = 5.0;
    return R1 * sin(theta);
}

int main(){
    Donut::initialXYcurve torusCurve = {torusEquationX, torusEquationY, 0, 2*M_PI};
    Donut donut(torusCurve, 10, 15, 50, 50);
    donut.rotating3D();
    // for(int i = 0; i < 50; i++){
    //     for(int j = 0; j < 50; j++){
    //         std::cout << 'a';
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}