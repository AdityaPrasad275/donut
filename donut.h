#include<bits/stdc++.h>
typedef std::vector<std::vector<float>> Matrix;
Matrix operator*(const Matrix &a, const Matrix &b);

class Donut
{
public:
    struct initialXYcurve{
        float (*equationX)(float);
        float (*equationY)(float);
        float startTheta;
        float endTheta;
    };
    Donut();
    Donut(initialXYcurve& _initCurve, float k1, float k2, int screenWidth, int screenHeight, float thetaSpacing = 0.07, float phiSpacing = 0.02);
    ~Donut();
    void rendering();

private:
    //how fine we want to draw the shape
    float thetaSpacing, phiSpacing;

    initialXYcurve _initialXYcurve;
    int screenWidth, screenHeight; 
    float k2, k1; //these handle the size and distance from screen of the our 3d shape

    Matrix calcCordsXYZ(float theta, float phi, float angleOfRotationAboutX, float angleOfRotationAboutZ);
    Matrix vectorRotator(Matrix &initVec,float phi, float angleOfRotationAboutX, float angleOfRotationAboutZ);
};

