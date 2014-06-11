#pragma once
#include <sifteo.h>
#include "QState.h"
#include "Component.h"

using namespace Sifteo;

class QBit : public Component{
public:
    QBit(unsigned id);
    
    QState getState();
    void setState(QState state);
    bool isLocked();
    void setLocked(bool lock);
    void update();
    void draw(RGB565 color);
    
private:
    QState state;
    bool locked; //Determina se o estado está travado ou não

};