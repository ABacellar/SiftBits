#include <sifteo.h>
#include "assets.gen.h"
#include "QBit.h"
#include "QState.h"
#include "Component.h"

using namespace Sifteo;

QBit::QBit(unsigned id) : Component(id){
    inputnum = 0;
    state = QState();
    locked = false;
}

QState QBit::getState(){
    return state;
}

void QBit::setState(QState state){
    this -> state = state;
}

bool QBit::isLocked(){
    return locked;
}

void QBit::setLocked(bool lock){
    locked = lock;
}

void QBit::update(){
    float r = pow(cos(getState().getRadians()), 2);
    float g = 0;
    float b = pow(sin(getState().getRadians()), 2);
    RGB565 color = RGB565::fromRGB(r, g, b);
    draw(color);
    output = &state;
}

void QBit::draw(RGB565 color){
    //vid[cube].initMode(SOLID_MODE);
    //vid[cube].initMode(BG0_SPR_BG1);
    int frame = getState().getDegrees()/15.0;
    if(frame < 0) frame += 24;
    if(frame > 24) frame -= 24;
    const AssetImage* asset = &Arrow;
    vid.bg0.image(vec(0, 0), *asset, frame);
}