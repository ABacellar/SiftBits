#include <Sifteo.h>
#include "QState.h"
#include "Gate.h"

using namespace Sifteo;

QState QState::null = QState(999, 999);

QState::QState(){
    theta = 0;
    phi = 0;
}

QState::QState(double t, double p){
    theta = t;
    phi = p;
}

bool QState::operator==(QState state){
    if(theta == state.theta && phi == state.phi) return true;
    else return false;
}

//Não usar
QState QState::operator*(Gate* gate){
    double alpha = cos(theta);
    double beta  = sin(theta);
    
    double a = gate -> getA();
    double b = gate -> getB();
    double c = gate -> getC();
    
    alpha = a*alpha + c*beta;
    beta  = c*alpha + b*beta;
    
    double rad = (1.0719*beta) - (0.3107*pow(beta, 3)) + (0.69582*pow(beta, 5));
    double degree = rad*(180.0/M_PI);
    
    QState state = QState(degree, phi);
    state.ajustRange();
    return state;
}

//Usar
QState QState::multiply(Gate gate){
    LOG("theta = %f\n", theta);
    double alpha = cos(M_PI*theta/180);
    double beta  = sin(M_PI*theta/180);
    
    LOG("alpha = %f\nbeta = %f\n", alpha, beta);
    
    double a = gate.getA();
    double b = gate.getB();
    double c = gate.getC();
    
    LOG("a = %f; b = %f; c = %f\n", a, b, c);
    
    double Alpha = a*alpha + c*beta;
    double Beta  = c*alpha + b*beta;
    
    LOG("Alpha = a*alpha + c*beta = %f*%f + %f*%f = %f\n", a, alpha, c, beta, Alpha);
    LOG("Beta = c*alpha + b*beta = %f*%f + %f*%f = %f\n", c, alpha, b, beta, Beta);
    
    double rad = (1.0719*Beta) - (0.3107*pow(Beta, 3)) + (0.69582*pow(Beta, 5));
    int degree = rad*(180.0/M_PI);
    int n = 15;
    degree = ((degree/n)*n) + ((int)((degree%n)/(n/2.0))*n);
    
    LOG("rad = %f\ndegree = %d\n\n", rad, degree);
    
    QState state = QState(degree, phi);
    state.ajustRange();
    return state;
}

double QState::getDegrees(){
    return theta;
}

double QState::getRadians(){
    return M_PI*theta/180;
}

double QState::getPhiDegrees(){
    return phi;
}

double QState::getPhiRadians(){
    return M_PI*phi/180;
}

void QState::setDegrees(double degrees){
    theta = degrees;
}

void QState::setRadians(double radians){
    theta = 180.0*radians/M_PI;
}

void QState::rotateDegrees(double degrees){
    theta += degrees;
    ajustRange();
}

void QState::rotateRadians(double radians){
    theta += 180.0*radians/M_PI;
    ajustRange();
}

void QState::ajustRange(){
    while(theta < 0 || theta >= 360 || phi < 0 || phi >= 360){
        if(theta < 0) theta += 360;
        if(theta >= 360) theta -= 360;
        if(phi < 0) phi += 360;
        if(phi >= 360) phi -= 360;
    }
}