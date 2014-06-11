#pragma once
#include <sifteo.h>

class Gate;

class QState{
public:
    static QState null; //Estado impossível, representando um estado vazio
    
    QState(); //Cria uma nova instância de um estado quântico com theta e phi = 0
    QState(double t, double p); //Cria uma nova instância de um estado quântico com theta = t e phi = p
    
    //Compara dois estados quânticos:
    //Retorna 'true' se e somente se os ângulos theta e phi de um estado são iguais ao do outro estado.
    bool operator==(QState state);
    
    //Produto matricial
    QState operator*(Gate* gate); //Não usar
    QState multiply(Gate gate); //Usar
    
    double getDegrees();
    double getRadians();
    
    void setDegrees(double degrees);
    void setRadians(double radians);
    
    //Rotaciona o ângulo theta em graus:
    //O ângulo passado como parâmetro é somado ao ângulo theta. Posteriormente:
    //Se theta > 360, theta -= 360; Se theta < 0, theta += 360
    void rotateDegrees(double degrees);
    
    //Rotaciona o ângulo theta em radianos:
    //O ângulo passado como parâmetro é somado ao ângulo theta. Posteriormente:
    //Se theta > 2*pi, theta -= 2*pi; Se theta < 0, theta += 2*pi
    void rotateRadians(double radians);
    
    double getPhiDegrees();
    double getPhiRadians();
    
private:
    double theta; //Ângulo theta em graus
    double phi; //Ângulo phi em graus
    
    void ajustRange(); //Certifica-se de que tanto o ângulo theta quanto o phi estão dentro do range de 0 a 360 graus exclusive

};