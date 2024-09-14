/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"
#include "Jogador.h"

const float GRAVIDADE = 10.0f;

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->jogador = criarJogador(
        (Vector2) {
            .x = GetScreenWidth() / 2,
            .y = GetScreenHeight() / 2
        },
        (Vector2) { 0 },
        (Vector2) {
            .x = 32,
            .y = 32
        },
        200.0f,
        -350.0f,
        BLUE
    );

    atualizarSondasColisaoJogador( &gw->jogador );

    const char *mapa = 
        "b                       b\n"
        "b                       b\n"
        "b           j           b\n"
        "b                       b\n"
        "b                       b\n"
        "b                       b\n"
        "b                       b\n"
        "b        bbbbbbbb       b\n"
        "b                       b\n"
        "b                       b\n"
        "b    bbbbbbbbbbbbbbbb   b\n"
        "b                       b\n"
        "b                       b\n"
        "bbbbbbbbbbbbbbbbbbbbbbbbb";

    processarMapa( gw, mapa );

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw->blocos );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();

    Jogador *jogador = &gw->jogador;
    int quantidadeBlocos = gw->quantidadeBlocos;
    Bloco *blocos = gw->blocos;

    processarEntradaJogador( jogador );
    atualizarJogador( jogador, delta );
    atualizarSondasColisaoJogador( jogador );

    resolverColisaoJogadorBlocos( jogador, quantidadeBlocos, blocos );
    atualizarSondasColisaoJogador( jogador );

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    desenharJogador( &gw->jogador );
    for ( int i = 0; i < gw->quantidadeBlocos; i++ ) {
        desenharBloco( &gw->blocos[i] );
    }

    EndDrawing();

}

void processarMapa( GameWorld *gw, const char *dadosMapa ) {

    // duas passadas:

    // passada 1: contagem de blocos
    const char *simbolo = dadosMapa;
    int quantidadeBlocos = 0;
    while ( *simbolo != '\0' ) {
        if ( *simbolo == 'b' ) {
            quantidadeBlocos++;
        }
        simbolo++;
    }

    gw->quantidadeBlocos = quantidadeBlocos;
    gw->blocos = (Bloco*) malloc( gw->quantidadeBlocos * sizeof( Bloco ) );
    
    // passada 2: criação
    int linha = 0;
    int coluna = 0;

    simbolo = dadosMapa;
    int k = 0;
    float dimensaoBloco = 32.0f;

    while ( *simbolo != '\0' ) {

        switch ( *simbolo ) {

            case 'j':
                gw->jogador.pos = (Vector2) {
                    .x = coluna * dimensaoBloco,
                    .y = linha * dimensaoBloco
                };
                break;
            
            case 'b':
                gw->blocos[k++] = (Bloco) {
                    .pos = {
                        .x = coluna * dimensaoBloco,
                        .y = linha * dimensaoBloco
                    },
                    .dim = {
                        .x = dimensaoBloco,
                        .y = dimensaoBloco
                    },
                    GREEN
                };
                break;

            case '\n':
                linha++;
                coluna = 0;
                break;
            
        }

        if ( *simbolo != '\n' ) {
            coluna++;
        }

        simbolo++;

    }

}