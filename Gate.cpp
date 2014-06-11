#include <Sifteo.h>
#include "assets.gen.h"
#include "Gate.h"
#include "QState.h"
#include "Component.h"

Gate::Gate(unsigned id, int inputs) : Component(id){
    inputnum = inputs;
    A = 0;
    B = 0;
    C = 0;
}

Gate::Gate(unsigned id, int inputs, double a, double b, double c) : Component(id){
    inputnum = inputs;
    A = a;
    B = b;
    C = c;
}

QState* Gate::operator*(QState* state){
    return state;//*this;
}

double Gate::getA(){
    return A;
}

double Gate::getB(){
    return B;
}

double Gate::getC(){
    return C;
}

void Gate::compute(){
    *inputs[0] = (*inputs[0]).multiply(*this);
    output = inputs[0];
    
    //Salvar para operações com qbits múltiplos
    /*QState result = QState();
    int i = 0;
    while(i < inputnum){
        QState input = *getInput(i);
        result = input.multiply(this);
    }
    *output = result;*/
}

void Gate::draw(int gate){
    LOG("drawing gate %d", gate);
    const AssetImage* asset = &Gates;
    vid.bg0.image(vec(0, 0), *asset, gate);
}