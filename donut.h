#include<bits/stdc++.h>

class donut
{
private:
    //how fine we want to draw the torus
    double thetaSpacing, phiSpacing;

    //a circle (in x-y plane) centered on (R2, 0, 0) with radius R1 is rotated about y axis to get torus
    int r1, r2;

    int screenWidth, screenHeight; 
    float k2;
    float K1 = screenWidth*k2*3/(8*(r1+r2));
    std::vector<float> calc_cords_XYZ(double theta, double phi, double angleOfRotationAboutX, double angleOfRotationAboutY);
    int calc_luminance();
public:
    donut(/* args */);
    ~donut();
    rendering();
};

