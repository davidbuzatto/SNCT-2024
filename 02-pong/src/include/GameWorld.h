/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Jogador.h"
#include "Bola.h"

#include "raylib/raylib.h"

typedef enum EstadoJogo {
    ESTADO_JOGO_PARADO,
    ESTADO_JOGO_EXECUTANDO
} EstadoJogo;

typedef struct GameWorld {
    Jogador jogador1;
    Jogador jogador2;
    Jogador *ultimoPontuar;
    Bola bola;
    EstadoJogo estado;
} GameWorld;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void resolverColisaoBolaJogador( Bola *bola, Jogador *jogador );
void pararJogo( GameWorld *gw );
void recomecarJogo( GameWorld *gw );
void desenharPlacar( GameWorld *gw );