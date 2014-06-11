#pragma once
#include <sifteo.h>
#include "QState.h"

using namespace Sifteo;

class Component{
public:
    Component(unsigned id);
    CubeID getCube();
    int ID;
    VideoBuffer vid;
    
    QState* getInputs();
    QState* getInput(int i);
    bool addInput(QState* input);
    bool removeInput(QState input);
    bool removeInput(int i);
    QState* getOutput();
    bool removeOutput();
    void setOutput(QState out);
    
    void compute(); //Realiza as opera��es necess�rias baseadas em seus inputs para o c�lculo do output
    
protected:
    CubeID cube; //Cubo associado com este componente
    
    QState* inputs[4] = {}; //Entradas do componente
    int inputnum = 0; //N�mero de entradas aplic�veis a este componente
    QState* output = NULL;

};