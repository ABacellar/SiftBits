#include <Sifteo.h>
#include "assets.gen.h"
#include "Sensor.h"
#include "QState.h"
#include "Component.h"

Sensor::Sensor(unsigned id) : Component(id){
    inputnum = 1;
    //vid.initMode(FB32);
}

QState Sensor::measure(){
    QState* input = inputs[0];
    if(input == NULL)return QState(0, 90);
    Sifteo::SystemTime time = Sifteo::SystemTime::now();
    Sifteo::Random rand = Sifteo::Random(time.uptimeNS());
    if(rand.chance(Sifteo::pow(Sifteo::cos((*input).getRadians()), (float)2.0))) return QState(0, (*input).getPhiDegrees());
    else return QState(90, (*input).getPhiDegrees());
}

void Sensor::compute(){
    QState result = measure();
    if((&result) == NULL) return;
    //Sifteo::FB32Drawable &draw = vid.fb32;
    //se result.getDegrees() == 0: r = 1.0, b = 0.0; se result.getDegrees() == 90: r = 0.0, b = 1.0
    Sifteo::RGB565 color = Sifteo::RGB565::fromRGB(1-(result.getDegrees()/90), 0.f, result.getDegrees()/90);
    vid.colormap[0].set(color);
    draw(result.getDegrees());
    *inputs[0] = result;
}

void Sensor::draw(int degrees){
    int frame = degrees/15.0;
    if(frame < 0) frame += 24;
    if(frame > 24) frame -= 24;
    const AssetImage* asset = &Arrow;
    vid.bg0.image(vec(0, 0), *asset, frame);
}