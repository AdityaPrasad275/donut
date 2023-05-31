#include<bits/stdc++.h>

typedef std::vector<std::vector<float>> Matrix;

class Donut
{
public:
    struct initialXYcurve{
        float (*equationX)(float);
        float (*equationY)(float);
        float startTheta;
        float endTheta;
    };
    Donut(initialXYcurve& _initCurve, float k2, int screenWidth, int screenHeight, float thetaSpacing = 0.5, float phiSpacing = 0.5);
    
    void renderObject();
private:
    initialXYcurve initCurve;

    Matrix allObjectVectors;
    Matrix allLuminanceVectors;

    float thetaSpacing, phiSpacing;
    int screenWidth, screenHeight; 
    float dis_objectFromScreen, dis_userFromScreen;

    float calc_dis_userFromScreen();
    void calc_allObjectVectors();
    void calc_allLuminanceVectors();

    Matrix rotate(float angleAbtX, float angleAbtZ, int i, Matrix &allVectors);
    std::vector<std::string> renderScreen(float angleAbtX, float angleAbtZ);
};