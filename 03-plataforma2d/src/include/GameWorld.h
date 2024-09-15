/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Jogador.h"
#include "Bloco.h"
#include "Item.h"
#include "Inimigo.h"

extern const float GRAVIDADE;

typedef struct GameWorld {
    
    Jogador jogador;

    int linhasMapa;
    int colunasMapa;
    Bloco *blocos;

    int quantidadeItens;
    Item *itens;

    int quantidadeInimigos;
    Inimigo *inimigos;

    Camera2D camera;

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

void processarMapa( GameWorld *gw, const char *dadosMapa, float dimensaoBlocos );
void atualizarCamera( GameWorld *gw );
void desenharHud( GameWorld *gw );
void tocarMusica( void );
Texture2D selecionarTile( char simbolo );
