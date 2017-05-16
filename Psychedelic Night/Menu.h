/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: rizado
 *
 * Created on May 9, 2017, 7:02 PM
 */

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
using namespace sf;
using namespace std;


class Menu {
public:
    Menu(float ancho, float alto);
    Menu(const Menu& orig);
    virtual ~Menu();
    void actualizar(int g);
    void Draw();
    void MoveUp();
    void MoveDown();
    void anyadiraSemilla(int a);
    int GetPressedItem(){return selecionarItem;}
    unsigned int getSemilla (){return semilla;}
private:
    int selecionarItem;
    Font fuente;
    vector<sf::Text*>* text;
    Texture fondo;
    Sprite *dibujo;
    bool act;
    unsigned int semilla;
    sf::Text text4;
    sf::Text text5;
};

#endif /* MENU_H */

