#pragma once
#include <sifteo.h>
#include "Component.h"

class QState;

class Gate : public Component{
public:

    Gate(unsigned id, int inputs);
    Gate(unsigned id, int inputs, double a, double b, double c);
    
    //Produto matricial
    QState* operator*(QState* state);
    
    void compute();
    void draw(int gate);
    
    double getA();
    double getB();
    double getC();
    
private:
    //Os três componentes de uma porta lógica {{a, c}, {c, b}}
    double A = 0;
    double B = 0;
    double C = 0;

};