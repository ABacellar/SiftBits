#include <sifteo/time.h>
#include <sifteo.h>
#include "assets.gen.h"
#include "Component.h"
#include "QBit.h"
#include "Gate.h"
#include "Sensor.h"
#include "QState.h"
using namespace Sifteo;

AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("Sensors SDK Example")
    .package("com.sifteo.sdk.siftbits", "1.1")
    .icon(Icon)
    .cubeRange(0, CUBE_ALLOCATION);

//static VideoBuffer vid[CUBE_ALLOCATION];
static TiltShakeRecognizer motion[CUBE_ALLOCATION];

int gate = 0;
Gate gates[3] = {Gate(0, 1, 1, -1, 0), Gate(0, 1, 0, 0, 1), Gate(0, 1, 1/sqrt(2.0), -1/sqrt(2.0), 1/sqrt(2.0))};
QBit qbit = QBit(1);
int sensor = 0;
Sensor sensors[1] = {Sensor(2)};

class SensorListener {
public:
    struct Counter {
    } counters[CUBE_ALLOCATION];

    void install()
    {
        Events::neighborAdd.set(&SensorListener::onNeighborAdd, this);
        Events::neighborRemove.set(&SensorListener::onNeighborRemove, this);
        Events::cubeAccelChange.set(&SensorListener::onAccelChange, this);
        Events::cubeTouch.set(&SensorListener::onTouch, this);
        Events::cubeConnect.set(&SensorListener::onConnect, this);

        // Handle already-connected cubes
        for (CubeID cube : CubeSet::connected()){
            onConnect(cube);
        }
    }

private:
    void onConnect(unsigned id)
    {
        CubeID cube(id);
        uint64_t hwid = cube.hwID();

        bzero(counters[id]);
        
        //if(id == 0)vid[cube].initMode(FB32);
        //if(id == 1)vid[cube].initMode(BG0_SPR_BG1);
        //if(id == 2)vid[cube].initMode(FB32);
        
        //vid[id].attach(id);
        motion[id].attach(id);
    }

    void onTouch(unsigned id){
        CubeID cube(id);
        
        if(id == 0){
            if(cube.isTouching()){
                gate++;
                if(gate > 2)gate = 0;
                if(gate == 0) LOG("Set gate to Z\n");
                else if(gate == 1) LOG("Set gate to X\n");
                else if(gate == 2) LOG("Set gate to H\n");
                gates[2].draw(gate);
            }
        }
        if(id == 1){
            if(cube.isTouching()){
                qbit.setLocked(!qbit.isLocked());
            }
        }
    }

    void onAccelChange(unsigned id){
        CubeID cube(id);
        auto accel = cube.accel();
        if(id == 1){
            if(!qbit.isLocked()){
                int n = 15;
                float sine = accel.x/64.0;
                float rad = (1.0719*sine) - (0.3107*pow(sine, 3)) + (0.69582*pow(sine, 5));
                int degree = rad*(180.0/M_PI);
                int angle = ((degree/n)*n) + ((int)((degree%n)/(n/2.0))*n);
                qbit.setState(QState(angle, qbit.getState().getPhiDegrees()));
                //DEBUG
                //LOG("sine: %f -> rad: %f -> degree: %d -> angle: %d\n", sine, rad, degree, angle);
            }
        }
        //qbit.update(vid);
    }

    void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide){
        
        if((firstID == 0 && secondID == 1) || (firstID == 1 && secondID == 0)){ //gate with qbit
            
            if(qbit.getOutput() != NULL) gates[gate].addInput(qbit.getOutput());
            gates[gate].compute();
        
        }
        if((firstID == 1 && secondID == 2) || (firstID == 2 && secondID == 1)){ //qbit with sensor
            
            if(qbit.getOutput() != NULL) sensors[sensor].addInput(qbit.getOutput());
            sensors[sensor].compute();
        }
        if((firstID == 0 && secondID == 2) || (firstID == 2 && secondID == 0)){ //gate with sensor
            
            if(gates[gate].getOutput() != NULL) sensors[sensor].addInput(qbit.getOutput());
            sensors[sensor].compute();
            
        }
    }
    
    void onNeighborRemove(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide){
        
        if((firstID == 0 && secondID == 1) || (firstID == 1 && secondID == 0)){ //gate with qbit
        
            gates[gate].removeInput(0);
            gates[gate].removeOutput();
            
        }
        if((firstID == 1 && secondID == 2) || (firstID == 2 && secondID == 1)){ //qbit with sensor
        
            sensors[sensor].removeInput(0);
            
        }
        if((firstID == 0 && secondID == 2) || (firstID == 2 && secondID == 0)){ //gate with sensor
        
            sensors[sensor].removeInput(0);
            
        }
    }
};

void main(){

    static SensorListener listener;
    listener.install();
    
    gates[2].draw(gate);

    while (1){
        qbit.update();
        System::paint();
    }
    
}
