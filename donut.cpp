#include "donut.h"
#include<conio.h>
typedef std::vector<std::vector<float>> Matrix;
typedef std::vector<std::string> Screen;
using std::cos;
using std::sin;
#define sleep(a) std::this_thread::sleep_for(std::chrono::milliseconds(a))

Donut::Donut(initialXYcurve &_initCurve, float k2, int screenWidth, int screenHeight, float thetaSpacing, float phiSpacing)
{
    this->initCurve = _initCurve;
    this->thetaSpacing = thetaSpacing;
    this->phiSpacing = phiSpacing;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->dis_objectFromScreen = k2;
    calc_allObjectVectors();
    calc_allLuminanceVectors();
    this->dis_userFromScreen = calc_dis_userFromScreen();
}

void Donut::renderObject()
{   
    float angleAbtX = 0.1f;
    float angleAbtZ = 0.1f;
    while(true){
        std::cout << std::string(100, '\n');

        //system("cls");
        Screen screen = renderScreen(angleAbtX, angleAbtZ);
        for(int i = 0; i < screen.size(); i++)
            std::cout << screen[i] << std::endl;

        sleep(100);
        angleAbtX += 0.1f;
        angleAbtZ += 0.1f;
    }
}

Screen Donut::renderScreen(float angleAbtX, float angleAbtZ)
{
    Matrix zBuffer(screenHeight, std::vector<float>(screenWidth, 0));
    Screen screen(screenHeight, std::string(screenWidth, ' '));

    for(int i = 0; i < allObjectVectors.size(); i++){
        Matrix coords = rotate(angleAbtX, angleAbtZ, i, allObjectVectors);
        float x = coords[0][0];
        float y = coords[0][1];
        float z = coords[0][2];
        float invZ = 1/z;

        int projectedX_index = (int)(screenWidth/2 + (dis_userFromScreen * x)/ (dis_objectFromScreen + dis_userFromScreen));
        int projectedY_index = (int)(screenHeight/2 + (dis_userFromScreen * y)/ (dis_objectFromScreen + dis_userFromScreen));

        Matrix luminanceVec = rotate(angleAbtX, angleAbtZ, i, allLuminanceVectors);
        float luminance = luminanceVec[0][1] - luminanceVec[0][2];
        //if(projectedX_index >= 0 && projectedX_index < screenWidth && projectedY_index >= 0 && projectedY_index < screenHeight){
        if (luminance>0){
            //if the z coordinate of the point is greater than the z coordinate of the point in the zBuffer
            if (zBuffer[projectedY_index][projectedX_index] > invZ){
                //update the z coordinate of the point in the zBuffer
                zBuffer[projectedY_index][projectedX_index] = invZ;
                //update the point in the screen vector
                screen[projectedY_index][projectedX_index] = ".,-~:;=!*#$@"[int(luminance * 10)];
            }
        }
        //}
    }
    return screen;
}

float Donut::calc_dis_userFromScreen()
{
    float maxDistance = 0;
    for (auto &objectVector : allObjectVectors){
        float x = objectVector[0];
        float y = objectVector[1];
        float x2 = x * x;
        float y2 = y * y;
        float distance = sqrt(x2 + y2);
        if (distance > maxDistance)
            maxDistance = distance;
    }
    if(maxDistance > dis_objectFromScreen){
        dis_objectFromScreen = maxDistance + 5;
        for(int i = 0; i < allObjectVectors.size(); i++)
            allObjectVectors[i][2] += maxDistance + 5;
    }
    
    if(maxDistance < (0.75f)*((float)std::min(screenHeight, screenWidth)))
        return dis_objectFromScreen;

    float k1 = (float)dis_objectFromScreen / (( 8.0f * maxDistance)/(3.0f*((float)std::min(screenHeight, screenWidth))) - 1.0f);
    return k1 < 0 ? dis_objectFromScreen : k1;
}

void Donut::calc_allObjectVectors()
{
    float theta = initCurve.startTheta;
    while(theta < initCurve.endTheta){
        float phi = 0;
        while(phi < 2*M_PI){
            float x = initCurve.equationX(theta);
            float y = initCurve.equationY(theta);
            float z = 0;
            allObjectVectors.push_back({x*cos(phi) - z*sin(phi), y, x*sin(phi) - z*sin(phi) + dis_objectFromScreen});
            phi += phiSpacing;
        }
        theta += thetaSpacing;
    }
}

void Donut::calc_allLuminanceVectors()
{
    float theta = initCurve.startTheta;
    while(theta < initCurve.endTheta){
        float phi = 0;
        while(phi < 2*M_PI){
            float x = cos(theta);
            float y = sin(theta);
            float z = 0;
            allLuminanceVectors.push_back({{x*cos(phi) - z*sin(phi), y, x*sin(phi) - z*sin(phi)}});
            phi += phiSpacing;
        }
        theta += thetaSpacing;
    }
}

Matrix Donut::rotate(float angleAbtX, float angleAbtZ, int i, Matrix &allVectors)
{
    float x = allVectors[i][0];
    float y = allVectors[i][1];
    float z = allVectors[i][2];
    float x1 = x*cos(angleAbtZ) - y*cos(angleAbtX)*sin(angleAbtZ) + z*sin(angleAbtX)*sin(angleAbtZ);
    float y1 = x*sin(angleAbtZ) + y*cos(angleAbtX)*cos(angleAbtZ) - z*sin(angleAbtX)*cos(angleAbtZ);
    float z1 = y*sin(angleAbtX) + z*cos(angleAbtX);
    return {{x1, y1, z1}};
}