/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoJugando.cpp
 * Author: drmonkey
 * 
 * Created on 11 de mayo de 2017, 10:42
 */
#include "EstadoJuego.h"
#include "MotorJuego.h"
#include "EstadoJugando.h"
#include "EstadoPausa.h"
#include "Motor2D.h"
#include "Vistas.h"
#include "Minimapa.h"
#include "HUD.h"
#define ktimeupdate 1000/15

EstadoJugando EstadoJugando::estjugando;

void EstadoJugando::Init(){
    niveles = new Nivel();
    Vistas* general = Vistas::Instance();
    general->centrarGeneral(niveles->getNivel());
    Minimapa* minimapa = Minimapa::Instance();
    HUD* hud = HUD::Instance();
    niveles->visitar(niveles->getX(), niveles->getY());
    personaje = new Jugador(39*20*3+ 39*20/2, 23*20*3+ 23*20/2);
    minimap=false;
    relojSprite.restart();
    timeStartUpdate =clock1.getElapsedTime();
}

void EstadoJugando::Init(unsigned int s){
    niveles = new Nivel(s);
    Vistas* general = Vistas::Instance();
    general->centrarGeneral(niveles->getNivel());
    Minimapa* minimapa = Minimapa::Instance();
    HUD* hud = HUD::Instance();
    niveles->visitar(niveles->getX(), niveles->getY());
    personaje = new Jugador(39*20*3+ 39*20/2, 23*20*3+ 23*20/2);
    minimap=false;
    relojSprite.restart();
    timeStartUpdate =clock1.getElapsedTime();
}

void EstadoJugando::Limpiar(){
    if (niveles!=NULL)
        delete niveles;
    if (personaje!=NULL)
        delete personaje; 
}

void EstadoJugando::Pausar(){
}

void EstadoJugando::Continuar(){
}

void EstadoJugando::ManejarEventos(MotorJuego* juego){
    if(clock1.getElapsedTime().asMilliseconds() - timeStartUpdate.asMilliseconds() > ktimeupdate){
        sf::Event event;
        Vistas* general = Vistas::Instance();
        if (juego->ventana->pollEvent(event)){
            if (event.type == sf::Event::Closed) 
                juego->Salir();
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::Escape:
                       juego->ApilarEstado(EstadoPausa::Instance()); 
                    break;
                    case sf::Keyboard::W: personaje->setFlagW(true); break;
                    case sf::Keyboard::A: personaje->setFlagA(true); break;
                    case sf::Keyboard::S: personaje->setFlagS(true); break;
                    case sf::Keyboard::D: personaje->setFlagD(true); break;
                    case sf::Keyboard::E: personaje->ponerBomba(); break;
                    case sf::Keyboard::Up: personaje->setDirDisparo(0); break;
                    case sf::Keyboard::Down: personaje->setDirDisparo(1); break;
                    case sf::Keyboard::Left: personaje->setDirDisparo(2); break;
                    case sf::Keyboard::Right: personaje->setDirDisparo(3); break;
                    //LOS CHETOS
                    case sf::Keyboard::Z: if (!minimap) minimap = true; else minimap = false; break;
                    case sf::Keyboard::X: personaje->aumentarVidaActual(); break;
                    case sf::Keyboard::B: juego->Reiniciar(EstadoJugando::Instance()); break;
                    //case sf::Keyboard::N: niveles->aumentanivel(); break;
                    case sf::Keyboard::C: general->setZoom(); break;
                }           
            }
            if (event.type == sf::Event::KeyReleased){
                switch (event.key.code){
                    case sf::Keyboard::W: personaje->setFlagW(false); break;
                    case sf::Keyboard::A: personaje->setFlagA(false); break;
                    case sf::Keyboard::S: personaje->setFlagS(false); break;
                    case sf::Keyboard::D: personaje->setFlagD(false); break;
                    case sf::Keyboard::Up : personaje->decrementarBala(); break;                    
                    case sf::Keyboard::Down: personaje->decrementarBala(); break; 
                    case sf::Keyboard::Left:  personaje->decrementarBala(); break;  
                    case sf::Keyboard::Right: personaje->decrementarBala(); break;              
                }
            }
        }
        if(general->getEstado()){ //Movimiento vistas segun personaje
            if (personaje->getX()<niveles->getX()*39*20){
                general->moverVista(-39*20, 0);
                niveles->visitar(niveles->getX()-1, niveles->getY());
            }
            else if(personaje->getX()>(niveles->getX()+1)*39*20){
                general->moverVista(39*20, 0); 
                niveles->visitar(niveles->getX()+1, niveles->getY());
            }        
            else if (personaje->getY()<niveles->getY()*23*20){
                general->moverVista(0, -23*20); 
                niveles->visitar(niveles->getX(), niveles->getY()-1); 
            }
            else if (personaje->getY()>(niveles->getY()+1)*23*20){
                general->moverVista(0, 23*20); 
                niveles->visitar(niveles->getX(), niveles->getY()+1); 
            }        
        }
    }
}

void EstadoJugando::Actualizar(MotorJuego* juego){
    if(clock1.getElapsedTime().asMilliseconds() - timeStartUpdate.asMilliseconds() > ktimeupdate){
        timeStartUpdate =clock1.getElapsedTime();
        Vistas* general = Vistas::Instance();
        if (!general->getEstado())
            general->actualizarVista();
        reloj.restart();
        /*int x = personaje->getX();
        int y =  personaje->getY();
        int velocidad = personaje->SPRITE_SPEED;
        if (personaje->getFlagA()){ x = x-velocidad;}
        if (personaje->getFlagW()){ y = y-velocidad;}
        if (personaje->getFlagD()){ x = x+velocidad;}
        if (personaje->getFlagS()){ y = y+velocidad;}
<<<<<<< Updated upstream
        if (!niveles->colision(x, y)){
            personaje->setX(x);
            personaje->setY(y);*/

        //if (!niveles->colision(x, y)){
            //personaje->setX(x);
            //personaje->setY(y);

            personaje->mover(relojSprite);
        //}
        personaje->disparar();
        tiempo = clock2.restart();
        niveles->actualizar(clock2, tiempo);
        
    }
}

void EstadoJugando::Dibujar(MotorJuego* juego){
    Motor2D* motor2D = Motor2D::Instance();
    motor2D->limpiarVentana();
    Vistas* general = Vistas::Instance();
    juego->ventana->setView(general->getGeneral());
    niveles->dibujarNivel();
    personaje->pintarbalas();
    personaje->pintar();
    HUD* hud = HUD::Instance();
    juego->ventana->setView(hud->getHUD());
    hud->dibujar();
    Minimapa* minimapa = Minimapa::Instance();
    juego->ventana->setView(minimapa->getMinimapa());
    if (!minimap)
        minimapa->dibujar();
    else
        minimapa->dibujartotal();
    motor2D->pintarVentana();
}

Nivel* EstadoJugando::getNiveles(){
    return niveles;
}

Jugador* EstadoJugando::getPersonaje(){
    return personaje;
}