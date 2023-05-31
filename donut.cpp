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

Donut::Donut(initialXYcurve& _initCurve, float k1, float k2, int screenWidth, int screenHeight, float thetaSpacing, float phiSpacing)
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
    Matrix init_xyz = {{_initialXYcurve.equationX(theta),
                       _initialXYcurve.equationY(theta),
                       0}};
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
                                    {0, cos(angleOfRotationAboutX), sin(angleOfRotationAboutX)},
                                    {0, -sin(angleOfRotationAboutX), cos(angleOfRotationAboutX)}};
    Matrix rotationAboutZ_matrix = {{cos(angleOfRotationAboutZ), sin(angleOfRotationAboutZ), 0},
                                    {-sin(angleOfRotationAboutZ), cos(angleOfRotationAboutZ), 0},
                                    {0, 0, 1}};
    Matrix finalVec = initVec * phi_matrix * rotationAboutX_matrix * rotationAboutZ_matrix;
    return finalVec;
}

float Donut::calcLunminace(float theta, float phi, float angleOfRotationAboutX, float angleOfRotationAboutZ)
{
    Matrix initNormalVec = {{std::cos(theta), std::sin(theta), 0}};
    Matrix finalNormalVec = vectorRotator(initNormalVec, phi, angleOfRotationAboutX, angleOfRotationAboutZ);
    return finalNormalVec[0][1] - finalNormalVec[0][2];
}

std::vector<std::string> Donut::rendering3Dobject(float angleOfRotationAboutX, float angleOfRotationAboutZ)
{
    //initialize a 2d vector of strings with size screen_widht and screen_height with spaces
    std::vector<std::string> screen(screenWidth, std::string(screenHeight, ' '));
    //initialize a 2d vector of floats with size screen_widht and screen_height with 0
    std::vector<std::vector<float>> zBuffer(screenWidth, std::vector<float>(screenHeight, 0));

    //loop through all the possible values of theta and phi
    for (float theta = _initialXYcurve.startTheta; theta < _initialXYcurve.endTheta; theta += thetaSpacing)
    {
        for (float phi = 0; phi < 2 * M_PI; phi += phiSpacing)
        {
            //calculate the x,y,z coordinates of the point
            Matrix xyz = calcCordsXYZ(theta, phi, angleOfRotationAboutX, angleOfRotationAboutZ);
            float x = xyz[0][0];
            float y = xyz[0][1];
            float z = k2 + xyz[0][2];
            float oneOverZ = 1/z;

            //calculate the luminance of the point
            float luminance = calcLunminace(theta, phi, angleOfRotationAboutX, angleOfRotationAboutZ);

            //calculate the index of the projected x,y coordinates in the screen vector
            int projectedX_index = (int)(screenWidth / 2 + k1*oneOverZ*x);
            int projectedY_index = (int)(screenHeight / 2 - k1*oneOverZ*y);

            if (luminance>0)
            {
                //if the z coordinate of the point is greater than the z coordinate of the point in the zBuffer
                if (zBuffer[projectedX_index][projectedY_index] < oneOverZ)
                {
                    //update the z coordinate of the point in the zBuffer
                    zBuffer[projectedX_index][projectedY_index] = oneOverZ;
                    //update the point in the screen vector
                    screen[projectedX_index][projectedY_index] = ".,-~:;=!*#$@"[int(luminance * 8)];
                }
            }
        }
    }
    return screen;
}

void Donut::rotating3D()
{
    float angleOfRotationAboutX = 0;
    float angleOfRotationAboutZ = 0;
    while (true)
    {
        //clear the screen
        system("CLS");
        //std::cout << std::string('\n', 100);
        //render the 3d object
        std::vector<std::string> screen = rendering3Dobject(angleOfRotationAboutX, angleOfRotationAboutZ);
        //print the screen
        for (int i = 0; i < screen.size(); i++)
        {
            std::cout << screen[i] << std::endl;
        }
        //update the angle of rotation
        angleOfRotationAboutX += 0.05;
        angleOfRotationAboutZ += 0.05;
        //sleep for some milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

