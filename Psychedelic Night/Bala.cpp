/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bala.cpp
 * Author: juli
 * 
 * Created on 25 de marzo de 2017, 11:47
 */
#include "Bala.h"
#include <stdio.h>
#include <iostream>

Bala::Bala(int x,int y,int velx, int vely, float rangoDisparo) {
    
    int r1 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    int r2 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    int r3 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    // posicion de inicio de la bal que coincide con jugador
    posx = x;
    posy = y;
    // direcc+ión y velocidad de la bala
    this->velx=velx;
    this->vely=vely;
    this->rangoDisparo = rangoDisparo;
    destruirBala = false;
    
    clock.restart();
    
    textura = new Texture();  
    if(!textura->loadFromFile("resources/bala.png")){
        std::cerr << "Error while loading texture ISAAC" << std::endl;
        return;
    };
    
    sprite = new Sprite(*textura);
    sprite->setTextureRect(sf::IntRect(16, 16, 32, 32));
    // fijar centroide
    sprite->setOrigin(16,16); 
    sprite->setScale(0.5,0.5);
    sprite->setColor(sf::Color(r1, r2, r3));
    
    this->angle=0;
    this->colisionObjeto=false;
    
}

Bala::~Bala() {
    delete sprite;
    delete textura;   
}


void Bala::colisionar(){     

    

}

void Bala::actualiza(){
    posx+=velx;
    posy+=vely;

    if(clock.getElapsedTime().asSeconds()< rangoDisparo){
        sprite->setPosition(posx,posy);  
    }
    else{
        destruirBala = true;}
    
    if(colisionObjeto==true){
        destruirBala=true;
    }
    
}

void Bala::actualiza2(){
    
    float lenght = 5+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/17));
    int tipoDirect = (int) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(4)));
    /*
    if(angle>0){
        angle=-angle;
        angle-=0.3;
    }else{
       angle=-angle;
       angle+=0.3;
        
    }*/
    
    angle+=0.3;
    
    if(tipoDirect==0){
    posx+=velx*cos(angle)+lenght;
    posy+=vely*sin(angle)+lenght; 
    }
    if(tipoDirect==1){
    posx-=velx*cos(angle)+lenght;
    posy-=vely*sin(angle)+lenght; 
    }
    if(tipoDirect==2){
    posx-=velx*cos(angle)+lenght;
    posy+=vely*sin(angle)+lenght; 
    }
    if(tipoDirect==3){
    posx+=velx*cos(angle)+lenght;
    posy-=vely*sin(angle)+lenght; 
    }
   

    if(clock.getElapsedTime().asSeconds()< rangoDisparo){
        sprite->setPosition(posx,posy);  
    }
    else{
        destruirBala = true;}
    
    if(colisionObjeto==true){
        destruirBala=true;
    }
    
}


void Bala::golpea(){
    colisionObjeto=true;
}
int Bala::getX(){
    return posx;
}

int Bala::getY(){
    return posy;
}


sf::Sprite Bala::getSprite(){
    return *sprite;
}

