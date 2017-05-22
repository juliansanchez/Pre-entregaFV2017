/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoMuerte.cpp
 * Author: drmonkey
 * 
 * Created on 22 de mayo de 2017, 18:48
 */

#include "EstadoMuerte.h"
#include "EstadoJugando.h"
#include "EstadoIntro.h"
#include "HUD.h"
#include "Minimapa.h"
#include "Vistas.h"

EstadoMuerte EstadoMuerte::estmuerte;

void EstadoMuerte::Init(){
    EstadoJugando* estjue = EstadoJugando::Instance();
    contador = 150;
    tex.loadFromFile("resources/isaacAzul.png");
    pj.setTexture(tex);
    pj.setOrigin(27/2, 32/2);
    pj.setPosition(estjue->getPersonaje()->getX(), estjue->getPersonaje()->getY()); 
    pj.setScale(1.5, 1.5);
    fuente.loadFromFile("resources/upheavtt.ttf");
    texto.setFont(fuente);
    texto.setString("Espacio para reiniciar o ESC para volver al menu");
    texto.setPosition(sf::Vector2f(40, 4*540/5));
}

void EstadoMuerte::Init(unsigned int sem){}


void EstadoMuerte::Limpiar(){
    
}

void EstadoMuerte::Pausar(){
    
}

void EstadoMuerte::Continuar(){
    
}

void EstadoMuerte::ManejarEventos(MotorJuego* juego){
    sf::Event event;
    if (juego->ventana->pollEvent(event)){
        if (event.type == sf::Event::Closed) 
            juego->Salir();
        if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Escape:
                    juego->Reiniciar(EstadoIntro::Instance()); 
                break;
                case sf::Keyboard::Space:
                    juego->Reiniciar(EstadoJugando::Instance());
                break;
            }
        }
    }
}

void EstadoMuerte::Actualizar(MotorJuego* juego){
    rec.setFillColor(sf::Color(0,0,0, 200/contador));
    texto.setFillColor(sf::Color(255,255,255, 200/contador));
    if (contador>2*150/3){
        pj.setTextureRect(sf:: IntRect(18, 153, 27, 32));
    }
    else if (contador>150/3){
        pj.setTextureRect(sf:: IntRect(148, 215, 27, 32));
    }
    else{
        pj.setTextureRect(sf:: IntRect(206, 162, 35, 27));
    }
    if (contador != 1){
        contador--;
    }
}

void EstadoMuerte::Dibujar(MotorJuego* juego){
    EstadoJugando* estjue = EstadoJugando::Instance();
    Motor2D* motor2D = Motor2D::Instance();
    motor2D->limpiarVentana();
    Vistas* general = Vistas::Instance();
    juego->ventana->setView(general->getGeneral());
    estjue->getNiveles()->dibujarNivel();
    motor2D->pintarSprites(pj);
    HUD* hud = HUD::Instance();
    juego->ventana->setView(hud->getHUD());
    hud->dibujar();
    Minimapa* minimapa = Minimapa::Instance();
    juego->ventana->setView(minimapa->getMinimapa());
    minimapa->dibujar();
    juego->ventana->setView(juego->ventana->getDefaultView());
    rec.setSize(juego->ventana->getDefaultView().getSize());
    motor2D->pintarRectShape(rec);
    motor2D->pintarTexto(texto);
    motor2D->pintarVentana();
}


