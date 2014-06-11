#include <Sifteo.h>
#include "Component.h"
#include "QState.h"

using namespace Sifteo;

Component::Component(unsigned id){
    CubeID c(id);
    cube = c;
    ID = id;
    vid.initMode(BG0_SPR_BG1);
    vid.attach(id);
}

CubeID Component::getCube(){
    return cube;
}

QState* Component::getInputs(){
    return *inputs;
}

QState* Component::getInput(int i){
    return inputs[i];
}

bool Component::addInput(QState* input){
    for(int i = 0; i < inputnum; i++){
        if(inputs[i] == NULL){
            inputs[i] = input;
            return true;
        }
    }
    return false;
}

bool Component::removeInput(QState input){
    for(int i = 0; i < inputnum; i++){
        if(inputs[i] == &input){
            inputs[i] = NULL;
            return true;
        }
    }
    return false;
}

bool Component::removeInput(int i){
    if(inputs[i] != NULL){
        inputs[i] = NULL;
        return true;
    }
    return false;
}

QState* Component::getOutput(){
    return output;
}

bool Component::removeOutput(){
    if(output != NULL){
        output = NULL;
        return true;
    }
    return false;
}

void Component::setOutput(QState out){
    *output = out;
}

void Component::compute(){
    LOG("Component compute()\n");
    //do nothing
}