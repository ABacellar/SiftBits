#pragma once
#include <sifteo.h>

class Gate;

class QState{
public:
    static QState null; //Estado imposs�vel, representando um estado vazio
    
    QState(); //Cria uma nova inst�ncia de um estado qu�ntico com theta e phi = 0
    QState(double t, double p); //Cria uma nova inst�ncia de um estado qu�ntico com theta = t e phi = p
    
    //Compara dois estados qu�nticos:
    //Retorna 'true' se e somente se os �ngulos theta e phi de um estado s�o iguais ao do outro estado.
    bool operator==(QState state);
    
    //Produto matricial
    QState operator*(Gate* gate); //N�o usar
    QState multiply(Gate gate); //Usar
    
    double getDegrees();
    double getRadians();
    
    void setDegrees(double degrees);
    void setRadians(double radians);
    
    //Rotaciona o �ngulo theta em graus:
    //O �ngulo passado como par�metro � somado ao �ngulo theta. Posteriormente:
    //Se theta > 360, theta -= 360; Se theta < 0, theta += 360
    void rotateDegrees(double degrees);
    
    //Rotaciona o �ngulo theta em radianos:
    //O �ngulo passado como par�metro � somado ao �ngulo theta. Posteriormente:
    //Se theta > 2*pi, theta -= 2*pi; Se theta < 0, theta += 2*pi
    void rotateRadians(double radians);
    
    double getPhiDegrees();
    double getPhiRadians();
    
private:
    double theta; //�ngulo theta em graus
    double phi; //�ngulo phi em graus
    
    void ajustRange(); //Certifica-se de que tanto o �ngulo theta quanto o phi est�o dentro do range de 0 a 360 graus exclusive

};