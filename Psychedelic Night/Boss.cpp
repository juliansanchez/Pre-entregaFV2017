/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boss.cpp
 * Author: rizado
 * 
 * Created on May 13, 2017, 4:08 PM
 */

#include "Boss.h"
#include "EstadoJugando.h"

Boss::Boss(int posX, int posY) {
    this->posMatrix_x= posX;
    this->posMatrix_y=posY;
    vida=30;
    
      
    
    Texture *textura3;
    textura3 = new Texture();
    if (!textura3->loadFromFile("resources/boss.png")) {
        cerr << "Error cargando la imagen";
        exit(0);
    }
    SpriteGame c(*textura3,14,67,65,129);
    SpriteGame c1(*textura3,89,152,9,60);
    SpriteGame c2(*textura3,6,73,9,60);
    SpriteGame c3(*textura3,86,155,71,125);
    
    ancho=c.getAncho()*2;
    alto=c.getAlto()*2;

    this->enemigo=new Sprite*[4];
    for(int i=0; i<4;i++){
        this->enemigo[i]= new Sprite ();
     }
    *this->enemigo[0]=c.GetSprite();
    *this->enemigo[1]=c1.GetSprite();
    *this->enemigo[2]=c2.GetSprite();
    *this->enemigo[3]=c3.GetSprite();
    
    for(int i=0; i<4;i++){
        this->enemigo[i]->setScale(2,2);
     }
    
    this->num_sprites=4;
    this->numCambio=16;
    this->cambio_sprite=0;   
    this->dispara=0;
    this->rangoDisparo = 1;
    contador_vueltas=0;
    retraso=0;
    retraso2=7;
    retraso3=0;
    balas= new std::vector<Bala*>;
    bicho=new std::vector<NPC*>;
    int initX =posMatrix_x*39*20 + 39*20/2 ;
    int initY =posMatrix_y*23*20 + 23*20/2 ;
    cont_colision=0;
    colision=false;
    for(int i=0;i<num_sprites;i++){
        this->enemigo[i]->setPosition(initX,initY);
    } 
    
}

Boss::Boss(const Boss& orig) {
}

Boss::~Boss() {
    while (!balas->empty()){
        delete balas->back();
        balas->pop_back(); 
    } 
    balas->clear();
    delete balas;
    while (!bicho->empty()){
        delete bicho->back();
        bicho->pop_back(); 
    } 
    bicho->clear();
    delete bicho;
    delete[] enemigo;
}

int Boss::getPosMatrix_x(){
    return this->posMatrix_x;
}

int Boss::getPosMatrix_y(){
    return this->posMatrix_y;
    
}

float Boss::getX(){
    return enemigo[cambio_sprite]->getPosition().x;
}

float Boss::getY(){
    return enemigo[cambio_sprite]->getPosition().y;  
}

void Boss::dibujarBoss(){
    Motor2D *motor2D = Motor2D::Instance();
    motor2D->pintarSprites(*this->enemigo[cambio_sprite]);
    for(int i = 0 ; i<balas->size(); i++){
        if(balas->at(i)){
           motor2D->pintarSprites(balas->at(i)->getSprite());
         }
    }
    for(int i = 0 ; i<bicho->size(); i++){
        if(bicho->at(i)){
           bicho->at(i)->dibujarEnemigo();
         }
    }
}


void Boss::movBoss(Clock clock2, Time tiempo){
    
    float distancia_x,distancia_y,distancia;
    float direcx, direcy;
    EstadoJugando* estandoJugando= EstadoJugando::Instance();
    
    distancia_x= (this->getX()) - (estandoJugando->getPersonaje()->getX());
    distancia_y= (this->getY()) - (estandoJugando->getPersonaje()->getY());
    distancia= sqrt(pow(distancia_x,2)+pow(distancia_x,2) );
    float signox ;
    float signoy ;
    if(distancia_x<=0){
        signox=1;
    }else{
        signox=-1;
    }
    if(distancia_y<=0){
        signoy=1;
    }else{
        signoy=-1;
    }

    
    if(contador_vueltas%this->numCambio==0){
        
        
        if(retraso3<15){
            for(int i=0; i<4;i++){
                this->enemigo[i]->move(signox*16,signoy*16);
                cambio_sprite=(cambio_sprite+1)%(this->num_sprites-2);
            }
        }else{
            for(int i=0; i<4;i++){
                this->enemigo[i]->move(-distancia_x/5,-distancia_y/5);
                cambio_sprite=2;

            }
            if(retraso3>20){
                retraso3=0;
            }
        }
        retraso3++;
        
        if(retraso==4){
            cambio_sprite=2;
            for(int i=0;i<2;i++){
                    
                direcx =  static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15));
                direcy =  static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15));
                
                balas->push_back(new Bala(enemigo[cambio_sprite]->getPosition().x,enemigo[cambio_sprite]->getPosition().y,signox*direcx,signoy*direcy,rangoDisparo));
                balas->push_back(new Bala(enemigo[cambio_sprite]->getPosition().x,enemigo[cambio_sprite]->getPosition().y,signoy*direcy,signox* direcx,rangoDisparo));
                balas->push_back(new Bala(enemigo[cambio_sprite]->getPosition().x,enemigo[cambio_sprite]->getPosition().y,-signox*direcx,-signoy*direcy,rangoDisparo));
                balas->push_back(new Bala(enemigo[cambio_sprite]->getPosition().x,enemigo[cambio_sprite]->getPosition().y,-signoy*direcy,-signox* direcx,rangoDisparo));
                balas->push_back(new Bala(enemigo[cambio_sprite]->getPosition().x,enemigo[cambio_sprite]->getPosition().y,-distancia_x/12,-distancia_y/12,rangoDisparo));

              
                
                if (signox <0){
                    signox = 1;
                }else{
                    signox = -1;
                }
                if (signoy < 0){
                    signoy =1;
                }else{
                    signox = -1;
                }
                dispara++;
            }
            retraso=0;
        }
        if(retraso2==18){
            cambio_sprite=3;
            for(int i=0;i<3;i++){
                bicho->push_back(new NPC(13,posMatrix_x,posMatrix_y));
                //posMatrix_x*39*20 + 39*20/2
                //posMatrix_y*23*20 + 23*20/2
            }
            for(int i = bicho->size()-3 ; i<bicho->size(); i++){
                if(bicho->at(i)){
                    bicho->at(i)->posicionAleatoria();                      
                }   
            }
            retraso2=0;
        }
        retraso++;
        retraso2++;
    } 
    this->ActualizarDisparo();
    for(int i = 0 ; i<bicho->size(); i++){
        if(bicho->at(i)){
            bicho->at(i)->nextSprite(contador_vueltas); 
            bicho->at(i)->movMosquito();                      
        }   
    }
    contador_vueltas++;
}


void Boss::ActualizarDisparo(){
    
        // actualizo posicion de la bala
        for(int i = 0 ; i<balas->size(); i++){
            if(balas->at(i)){
                balas->at(i)->actualiza2(); // actualizo posicion de la bala
                if(balas->at(i)->destruirBala){
                    delete balas->at(i); // borramos la bala del vector
                    balas->erase(balas->begin()+i); // libero memoria de pos del vector
                }        
            }
        }

}


void Boss::colisionBoss(){
    
     EstadoJugando* estandoJugando= EstadoJugando::Instance();

    if(tipo !=2){ 
        if((estandoJugando->getPersonaje()->getX()+32) > (this->getX())&&  
                (estandoJugando->getPersonaje()->getY()+42) > (this->getY()) &&
                (this->getX()+this->enemigo[cambio_sprite]->getTextureRect().width)> (estandoJugando->getPersonaje()->getX()) &&
                (this->getY()+this->enemigo[cambio_sprite]->getTextureRect().height)> (estandoJugando->getPersonaje()->getY())){

            if(!colision){
                estandoJugando->getPersonaje()->quitarVida();
                colision=true;

            }else{
                if(cont_colision>25){
                    cont_colision=25; 
                }
                if(cont_colision==25){
                    colision=false;
                    cont_colision=0;
                }
            }
        }
    }
    if(colision){
      cont_colision++;
     }
     
}

void Boss::colisionBalasBoss(){
    
    EstadoJugando* estandoJugando= EstadoJugando::Instance();
       
    for(int i = 0 ; i<balas->size(); i++){
        if(balas->at(i)){
            
            if((estandoJugando->getPersonaje()->getX()+32) > (balas->at(i)->getX())&&  
                (estandoJugando->getPersonaje()->getY()+42) > (balas->at(i)->getY()) &&
                (balas->at(i)->getX()+16)> (estandoJugando->getPersonaje()->getX()) &&
                (balas->at(i)->getY()+16)> (estandoJugando->getPersonaje()->getY())){
                estandoJugando->getPersonaje()->quitarVida();
                balas->at(i)->golpea();
            }     
        }
    }    
}

void Boss::quitarVida(int herida){

    vida=vida-herida;
}