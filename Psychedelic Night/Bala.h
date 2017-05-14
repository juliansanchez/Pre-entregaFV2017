/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bala.h
 * Author: juli
 *
 * Created on 25 de marzo de 2017, 11:47
 */

#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;
using namespace std;
class Bala {
public:
    Bala(int x,int y,int velx, int vely, float rangoDisparo);
    Bala(const Bala& orig);
    ~Bala();
    
    void colisionar();
    void actualiza();
    int getX();
    int getY();
    bool destruirBala;
    sf::Sprite getSprite(); 
    void golpea();
private:    
    int posx;
    int posy;
    int velx;
    int vely;
    float rangoDisparo;
    bool colisionObjeto;
    
    sf::Texture *textura;
    sf::Sprite *sprite;
    sf::Clock clock; // controlar vida de la bala
};

#endif /* BALA_H */