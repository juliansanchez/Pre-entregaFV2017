/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoIntro.cpp
 * Author: mrmonkey
 * 
 * Created on 10 de mayo de 2017, 13:20
 */
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>

#include "MotorJuego.h"
#include "EstadoJuego.h"
#include "EstadoIntro.h"
#include "EstadoJugando.h"
#include "Menu.h"
#include "Vistas.h"

EstadoIntro EstadoIntro::estintro;

void EstadoIntro::Init(){
    //Carga animaciones intro si las hacemos
    menu = new Menu(900, 540);
    if(!music.openFromFile("resources/theme.ogg")){        
    }   
    music.play();      
    if(!efecto_click.loadFromFile("resources/connected-01.wav")){
    }
    if(!efecto_paso.loadFromFile("resources/poka03.ogg")){
    }   
    aceptar.setBuffer(efecto_click);    
    pasar.setBuffer(efecto_paso);
    printf("EstadoIntro iniciado\n");
}

void EstadoIntro::Init(unsigned int sem){}

void EstadoIntro::Limpiar(){
    delete menu;
    printf("Limpieza EstadoIntro\n");
}

void EstadoIntro::Pausar(){
    printf("Pausa EstadoIntro\n");
}

void EstadoIntro::Continuar(){
    printf("Continuar EstadoIntro");
}

void EstadoIntro::ManejarEventos(MotorJuego* juego){
    sf::Event event;
    if (juego->ventana->pollEvent(event)){
        if (event.type == sf::Event::Closed) 
            juego->Salir();
        if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){ 
                case sf::Keyboard::Escape:
                    juego->Salir();
                break;
                case sf::Keyboard::Up:
                    pasar.play();
                    menu->MoveUp();
                break;
                case sf::Keyboard::Down:
                    menu->MoveDown();
                    pasar.play();
                break;
                case sf::Keyboard::Space:
                    aceptar.play();
                    switch (menu->GetPressedItem()){
                        case 0:
                            if (menu->getSemilla()==0)
                                juego->Reiniciar(EstadoJugando::Instance());
                            else 
                                juego->Reiniciar(EstadoJugando::Instance(), menu->getSemilla());
                        break;
                        case 1:
                            //OPCIONES                            
                        break;
                        case 2:
                            juego->Salir();
                        break; 
                        case 3:
                            juego->DesapilarEstado();
                    }
                break;
                case sf::Keyboard::Num0:
                    menu->anyadiraSemilla(0);
                break;
                case sf::Keyboard::Num1:
                    menu->anyadiraSemilla(1);
                break;
                case sf::Keyboard::Num2:
                    menu->anyadiraSemilla(2);
                break;
                case sf::Keyboard::Num3:
                    menu->anyadiraSemilla(3);
                break;
                case sf::Keyboard::Num4:
                    menu->anyadiraSemilla(4);
                break;
                case sf::Keyboard::Num5:
                    menu->anyadiraSemilla(5);
                break;
                case sf::Keyboard::Num6:
                    menu->anyadiraSemilla(6);
                break;
                case sf::Keyboard::Num7:
                    menu->anyadiraSemilla(7);
                break;
                case sf::Keyboard::Num8:
                    menu->anyadiraSemilla(8);
                break;
                case sf::Keyboard::Num9:
                    menu->anyadiraSemilla(9);
                break;                   
            }           
        }		
    }
}

void EstadoIntro::Actualizar(MotorJuego* juego){
    menu->actualizar(juego->getTam());
}

void EstadoIntro::Dibujar(MotorJuego* juego){
    juego->ventana->setView(juego->ventana->getDefaultView());
    Motor2D* motor2D = Motor2D::Instance();
    motor2D->limpiarVentana();
    menu->Draw();
    motor2D->pintarVentana();
}




