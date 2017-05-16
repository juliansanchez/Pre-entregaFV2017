/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nivel.cpp
 * Author: drmonkey
 * 
 * Created on 29 de marzo de 2017, 12:56
 */
#include <iostream>
#include <stdlib.h>
#include <time.h> //Para la semilla
//#include <string>
#include "Nivel.h"
#include "EstadoJugando.h"
#include "Minimapa.h"
#include "Vistas.h"
#include <sstream>


using namespace std;

Nivel::Nivel() {
    unsigned int e = static_cast <unsigned> (time(0));
    //semilla = to_string(e);
    //unsigned int semi = stoi(semilla);
    stringstream convert;
    string result;
    convert<<e;
    result=convert.str();
    semilla=result;
    srand (e);
    n = 1;
    pl = new Planta(n+5);
    posx = (n+5)/2;
    posy = (n+5)/2;
    visitadas = new bool*[n+5];
    for (int i = 0; i<n+5; i++){
        visitadas[i] = new bool [n+5];
        for (int j = 0; j<n+5; j++)
            visitadas[i][j] = false;        
    }
    crearMapa();
}

Nivel::Nivel(unsigned int sem){
    //semilla = to_string(sem);
    stringstream convert;
    string result;
    convert<<sem;
    result=convert.str();
    semilla=result;
    srand(sem);
    n = 1;
    pl = new Planta(n+5);
    posx = (n+5)/2;
    posy = (n+5)/2;
    visitadas = new bool*[n+5];
    for (int i = 0; i<n+5; i++){
        visitadas[i] = new bool [n+5];
        for (int j = 0; j<n+5; j++)
            visitadas[i][j] = false;        
    }
    crearMapa(); 
                
}

Nivel::Nivel(const Nivel& orig) {
}

Nivel::~Nivel() {
    while (!vectorenemigos->empty()){
        delete vectorenemigos->back();
        vectorenemigos->pop_back();
    } 
    vectorenemigos->clear();
    delete vectorenemigos;
    delete tesoro;
    delete boss;
    for (int i = 0; i<n+5; i++){
        delete[] visitadas[i];
    }
    delete[] visitadas; 
    delete mapa;
    delete pl;
}

void Nivel::crearMapa(){
    vectorenemigos = new std::vector<NPC*>;
    mapa = new Mapa();
    int p = pl->getHabitaciones();
    mapa->leerMapa(p);
    int c = 0;
    int** matriz = pl->getMatriz();
    
    for (int i = 0; i<pl->getTam(); i++){
        for (int j = 0; j<pl->getTam(); j++){
            if (matriz[i][j] == 1 || matriz[i][j] == 2 || matriz[i][j] == 4 || matriz[i][j] == 5){
                mapa->setPosition(c, j, i);
                c++;
            }
            if (matriz[i][j] == 1){
                int r= 1 + (int) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
                for (int q = 0; q<i; q++){
                    int w = (int) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(3)));
                    vectorenemigos->push_back(new NPC(w, j, i));
                }
            }            
            else if (matriz[i][j] == 5){ //Carga tesoro
                int tipo = 0;
                float b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
                if (b>=0.5) tipo = 1;
                else tipo = 2;
                tesoro = new Modificador (39*20*j + 39*20/2, 23*20*i + 23*20/2, tipo);
            }
              else if (matriz[i][j] == 4){
                  boss= new Boss(j,i);
                  tex.loadFromFile("resources/trampilla.png");
                  trampilla.setTexture(tex);
                  trampilla.setOrigin(35/2, 35/2);
                  trampilla.setTextureRect(sf::IntRect(14, 14, 35, 35));
                  trampilla.setPosition(39*20*j + 39*20/2, 23*20*i + 23*20/2);
            }
        }
    }
}

void Nivel::dibujarNivel(){
    mapa->dibuja(pl->getHabitaciones());
    for (int i = 0; i<vectorenemigos->size(); i++){
        if (vectorenemigos->at(i)->getPosMatrix_x() == posx && vectorenemigos->at(i)->getPosMatrix_y() == posy){
            vectorenemigos->at(i)->pintarDisparo();
            vectorenemigos->at(i)->dibujarEnemigo();
        }
    }
    if (tesoro!=NULL)
        tesoro->pintar();
    if (boss!=NULL)
        boss->dibujarBoss();
    else {
        Motor2D* motor2D = Motor2D::Instance();
        motor2D->pintarSprites(trampilla);
    }
}

void Nivel::aumentanivel(){ 
    while (!vectorenemigos->empty()){
        delete vectorenemigos->back();
        vectorenemigos->pop_back();
    } 
    vectorenemigos->clear();
    delete vectorenemigos;
    delete tesoro;
    delete boss;
    for (int i = 0; i<n+5; i++){
        delete[] visitadas[i];
    }
    delete[] visitadas; 
    delete mapa;
    delete pl;
    
    n++;
    pl = new Planta (n+5);
    posx = (n+5)/2;
    posy = (n+5)/2;
    crearMapa();
    visitadas = new bool*[n+5];
    for (int i = 0; i<n+5; i++){
        visitadas[i] = new bool [n+5];
        for (int j = 0; j<n+5; j++)
            visitadas[i][j] = false;        
    }
    visitar(posx, posy);
    Vistas* g = Vistas::Instance();
    g->centrarGeneral(n);
}

string Nivel::getSemilla(){
    return semilla;
}

void Nivel::imprimir(){
    pl->imprimir();
}

int Nivel::getNivel(){
    return n;
}

void Nivel::actualizar(sf::Clock cl, sf::Time tim){
    Motor2D* motor2D = Motor2D::Instance();
    EstadoJugando* estandoJugando= EstadoJugando::Instance();
    for (int i = 0; i<vectorenemigos->size(); i++){
        if (vectorenemigos->at(i)->getPosMatrix_x() == posx && vectorenemigos->at(i)->getPosMatrix_y() == posy){
            vectorenemigos->at(i)->accionesEnemigo(cl, tim);
            vectorenemigos->at(i)->colisionPersonaje();
            vectorenemigos->at(i)->colisionBalasPersonaje();
        }
    }
    if (boss!=NULL && boss->getPosMatrix_x() == posx && boss->getPosMatrix_y() == posy)
        boss->movBoss(cl,tim);
    else{
         //IF que compruebe la colision del jugador con el sprite trampilla
    }
    
    if (tesoro!=NULL)
        tesoro->colisionObjeto(estandoJugando->getPersonaje());
    this->colisionEntreNPC();
    this->colisionBalasEnemigo();  
}


void Nivel::colisionBalasEnemigo(){

  EstadoJugando* estandoJugando= EstadoJugando::Instance();


  for(int i = 0 ; i<estandoJugando->getPersonaje()->getMunicion()->size(); i++){
      for (int j = 0; j<vectorenemigos->size(); j++){
          if (vectorenemigos->at(j)->getPosMatrix_x() == posx && vectorenemigos->at(j)->getPosMatrix_y() == posy){

                    
            if((vectorenemigos->at(j)->getX()+vectorenemigos->at(j)->getAnchoSprite()) > (estandoJugando->getPersonaje()->getMunicion()->at(i)->getX())&&  
                (vectorenemigos->at(j)->getY()+vectorenemigos->at(j)->getAltoSprite()) > (estandoJugando->getPersonaje()->getMunicion()->at(i)->getY())&&
                (estandoJugando->getPersonaje()->getMunicion()->at(i)->getX()+16)> (vectorenemigos->at(j)->getX()) &&
                (estandoJugando->getPersonaje()->getMunicion()->at(i)->getY()+16)> (vectorenemigos->at(j)->getY())){

                estandoJugando->getPersonaje()->getMunicion()->at(i)->golpea(); 
                vectorenemigos->at(j)->quitarVida(estandoJugando->getPersonaje()->getDanyo());
                if(vectorenemigos->at(j)->getVida()<=0){
                    delete vectorenemigos->at(j);
                    vectorenemigos->erase(vectorenemigos->begin() + j);
                }
            }                          
        }
      }   
   }
}

void Nivel::colisionEntreNPC(){
  for(int i = 0; i<vectorenemigos->size(); i++){
      for (int j = 0; j<vectorenemigos->size(); j++){
          if (vectorenemigos->at(j)->getPosMatrix_x() == posx && vectorenemigos->at(j)->getPosMatrix_y() == posy){ 
                if (vectorenemigos->at(i)->getPosMatrix_x() == posx && vectorenemigos->at(i)->getPosMatrix_y() == posy){
                    if (vectorenemigos->at(i)!=NULL && vectorenemigos->at(j)!=NULL){
                        if(i != j){
                            if((vectorenemigos->at(j)->getX()+vectorenemigos->at(j)->getAnchoSprite()) > (vectorenemigos->at(i)->getX())&&  
                                (vectorenemigos->at(j)->getY()+vectorenemigos->at(j)->getAltoSprite()) > (vectorenemigos->at(i)->getY())&&
                                (vectorenemigos->at(i)->getX()+vectorenemigos->at(i)->getAnchoSprite())> (vectorenemigos->at(j)->getX()) &&
                                (vectorenemigos->at(i)->getY()+vectorenemigos->at(i)->getAltoSprite())> (vectorenemigos->at(j)->getY())){
                                cout<<"entro"<<endl;
                                vectorenemigos->at(i)->posicionAnterior();
                                
                            }                       
                        } 
                    }
                }
             }
        }   
    }
}

bool **Nivel::getVisitadas(){
    return visitadas;
}

void Nivel::visitar(int i, int j){
    visitadas[i][j] = true;
    setX(i);
    setY(j);
}

int Nivel::getX(){
    return posx;
}

int Nivel::getY(){
    return posy;
}

void Nivel::setX(int x) {
    posx = x;
}

void Nivel::setY(int y){
    posy = y;
}
int** Nivel::getMatriz(){
    return pl->getMatriz();
}