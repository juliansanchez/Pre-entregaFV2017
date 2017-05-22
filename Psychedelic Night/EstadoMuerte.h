/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EstadoMuerte.h
 * Author: drmonkey
 *
 * Created on 22 de mayo de 2017, 18:48
 */

#ifndef ESTADOMUERTE_H
#define ESTADOMUERTE_H
#include "Jugador.h"
#include "EstadoJuego.h"

class EstadoMuerte : public EstadoJuego{
public:
    void Init();
    void Init(unsigned int sem);
    void Limpiar();
    void Pausar();
    void Continuar();
    void ManejarEventos(MotorJuego* juego);
    void Actualizar(MotorJuego* juego);
    void Dibujar(MotorJuego* juego);
    static EstadoMuerte* Instance() {
	return &estmuerte;
    }
protected:
    EstadoMuerte(){}
private:
    static EstadoMuerte estmuerte;
    Jugador *personaje;
    int contador;
    sf::RectangleShape rec;
    sf::Sprite pj;
    sf::Texture tex;
    sf::Font fuente;
    sf::Text texto;
};

#endif /* ESTADOMUERTE_H */

