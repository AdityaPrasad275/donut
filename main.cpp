#include"donut.h"

float torusEquationX(float theta) {
    float R1 = 2.0;
    float R2 = 7.0;
    return R2 + R1 * cos(theta);
}

float torusEquationY(float theta) {
    float R1 = 2.0;
    return R1 * sin(theta);
}

float cylinderEquationX(float theta){
    float R = 10.0;
    return R;
}
float cylinderEquationY(float theta){
    float h = 30.0;
    return h * sin(theta);
}

int main()
{
    Donut::initialXYcurve initCurve;
    initCurve.equationX = cylinderEquationX;
    initCurve.equationY = cylinderEquationY;
    initCurve.startTheta = -M_PI/2;
    initCurve.endTheta = M_PI/2;
    Donut donut(initCurve, 15, 50, 50, 0.07, 0.02);
    donut.renderObject();
    return 0;
}