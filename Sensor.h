#pragma once
#include <sifteo.h>
#include "Component.h"
#include "QState.h"

class Sensor : public Component{
public:

    Sensor(unsigned id);
    
    QState measure();
    void compute();
    void draw(int degrees);

};