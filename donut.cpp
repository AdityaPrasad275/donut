#include"donut.h"
typedef std::vector<std::vector<float>> Matrix;

Matrix operator*(const Matrix &a, const Matrix &b)
{
    Matrix c(a.size(), std::vector<float>(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            for (int k = 0; k < b.size(); k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

Donut::Donut(){

}

Donut::~Donut(){

}

Donut::Donut(initialXYcurve& _initCurve, float k1, float k2, int screenWidth, int screenHeight, float thetaSpacing = 0.07, float phiSpacing = 0.02)
{
    this->_initialXYcurve = _initCurve;
    this->k1 = k1;
    this->k2 = k2;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->thetaSpacing = thetaSpacing;
    this->phiSpacing = phiSpacing;
}

Matrix Donut::calcCordsXYZ(float theta, float phi, float angleOfRotationAboutX, float angleOfRotationAboutZ)
{
    Matrix init_xyz = {{_initialXYcurve.equationX(theta)},
                       {_initialXYcurve.equationY(theta)},
                       {0}};
    return vectorRotator(init_xyz, phi, angleOfRotationAboutX, angleOfRotationAboutZ);
}

Matrix Donut::vectorRotator(Matrix &initVec, float phi, float angleOfRotationAboutX, float angleOfRotationAboutZ)
{
    
    using std::cos;
    using std::sin;

    Matrix phi_matrix = {{cos(phi), 0, sin(phi)},
                         {0, 1, 0},
                         {-sin(phi), 0, cos(phi)}};
    Matrix rotationAboutX_matrix = {{1, 0, 0},
                                    {0, cos(angleOfRotationAboutX), -sin(angleOfRotationAboutX)},
                                    {0, sin(angleOfRotationAboutX), cos(angleOfRotationAboutX)}};
    Matrix rotationAboutZ_matrix = {{cos(angleOfRotationAboutZ), -sin(angleOfRotationAboutZ), 0},
                                    {sin(angleOfRotationAboutZ), cos(angleOfRotationAboutZ), 0},
                                    {0, 0, 1}};
    Matrix finalVec = initVec * phi_matrix * rotationAboutX_matrix * rotationAboutZ_matrix;
    return finalVec;
}

void Donut::rendering()
{
}

