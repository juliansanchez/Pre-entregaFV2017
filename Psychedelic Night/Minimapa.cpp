/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Minimapa.cpp
 * Author: drmonkey
 * 
 * Created on 9 de mayo de 2017, 14:40
 */

#include "Minimapa.h"
#include "EstadoJugando.h"

Minimapa* Minimapa::instanciaMinimapa = 0;

Minimapa::Minimapa() {
    minimapa.setViewport(sf::FloatRect(0.8f, 0.f, 0.2f, 0.2f));
    minimapa.zoom(1.f);
    rec.setSize(minimapa.getSize());
    rec.setFillColor(sf::Color(0,0,0, 140));
    vec = new vector<sf::RectangleShape*>;
}

Minimapa::Minimapa(const Minimapa& orig) {
}

Minimapa::~Minimapa() {
    while (!vec->empty()){
        delete vec->back();
        vec->pop_back();
        vec->clear();
    } 
    delete vec;
}

Minimapa* Minimapa::Instance(){
    if(instanciaMinimapa == 0)
        instanciaMinimapa = new Minimapa;  
    return instanciaMinimapa;
}

sf::View Minimapa::getMinimapa(){
    return minimapa;
}

void Minimapa::dibujar(){
    while (!vec->empty()){
        delete vec->back();
        vec->pop_back();
        vec->clear();
    }       
    Motor2D*motor2D = Motor2D::Instance();
    motor2D->pintarRectShape(rec);
    EstadoJugando* estjue = EstadoJugando::Instance();
    Nivel* nivel = estjue->getNiveles();
    bool **visitadas = nivel->getVisitadas();
    for (int i = 0; i<nivel->getNivel()+5; i++){
        for (int j = 0; j<nivel->getNivel()+5; j++){
            if (visitadas[i][j] == true){
                sf::RectangleShape* rectan = new sf::RectangleShape(sf::Vector2f(150, 75));
                if (nivel->getX() == i && nivel->getY() == j)
                    rectan->setFillColor(sf::Color::White);
                else
                    rectan->setFillColor(sf::Color(192,192,192));
                rectan->setPosition(150 + 150*i, 75 + 75*j);
                vec->push_back(rectan);
                motor2D->pintarRectShape(*rectan);
            }
        }
    }
}

void Minimapa::dibujartotal(){
    while (!vec->empty()){
        delete vec->back();
        vec->pop_back();
        vec->clear();
    }
    Motor2D*motor2D = Motor2D::Instance();
    motor2D->pintarRectShape(rec);
    EstadoJugando* estjue = EstadoJugando::Instance();
    Nivel* nivel = estjue->getNiveles();
    int** m = nivel->getMatriz();
    for (int i = 0; i<nivel->getNivel()+5; i++){
        for (int j = 0; j<nivel->getNivel()+5; j++){
            if (m[i][j]!= 0 && m[i][j]!=3){
                sf::RectangleShape* rectan = new sf::RectangleShape(sf::Vector2f(150, 75));
                if (nivel->getX() == j && nivel->getY() == i)
                    rectan->setFillColor(sf::Color::White);                
                else if (m[i][j] == 1 || m[i][j] == 2)
                    rectan->setFillColor(sf::Color(192,192,192));
                else if (m[i][j] == 4)
                    rectan->setFillColor(sf::Color::Red);
                else if (m[i][j] == 5)
                    rectan->setFillColor(sf::Color::Yellow);
                rectan->setPosition(150 + 150*j, 75 + 75*i);
                vec->push_back(rectan);
                motor2D->pintarRectShape(*rectan);                 
            }
        }
    }
}