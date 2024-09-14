/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "GameWorld.h"
#include "Jogador.h"
#include "Bola.h"

#include "raylib.h"

const float VELOCIDADE_MOVIMENTO_JOGADOR = 200.0f;
const float VELOCIDADE_MOVIMENTO_BOLA = 200.0f;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    //GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    GameWorld *gw = (GameWorld*) calloc( 1, sizeof( GameWorld ) );

    gw->jogador1 = criarJogador( 
        (Vector2){ 30.0f, GetScreenHeight() / 2 },
        (Vector2){ 0.0f, 0.0f },
        (Vector2){ 20.0f, 120.0f },
        WHITE
    );

    gw->jogador2 = criarJogador( 
        (Vector2){ GetScreenWidth() - 30.0f, GetScreenHeight() / 2 },
        (Vector2){ 0.0f, 0.0f },
        (Vector2){ 20.0f, 120.0f },
        WHITE
    );

    gw->bola = criarBola(
        (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 },
        (Vector2){ 0.0f, 0.0f },
        20.0f,
        WHITE
    );

    gw->estado = ESTADO_JOGO_PARADO;

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();

    Jogador *jogador1 = &gw->jogador1;
    Jogador *jogador2 = &gw->jogador2;
    Bola *bola = &gw->bola;

    if ( gw->estado == ESTADO_JOGO_EXECUTANDO ) {

        processarEntradaJogador( jogador1, KEY_W, KEY_S, VELOCIDADE_MOVIMENTO_JOGADOR );
        processarEntradaJogador( jogador2, KEY_UP, KEY_DOWN, VELOCIDADE_MOVIMENTO_JOGADOR );

        atualizarJogador( jogador1, delta );
        atualizarJogador( jogador2, delta );

        switch ( atualizarBola( bola, delta ) ) {
            case COLISAO_LATERAL_BOLA_ESQUERDA:
                jogador2->pontuacao++;
                gw->ultimoPontuar = jogador2;
                pararJogo( gw );
                break;
            case COLISAO_LATERAL_BOLA_DIREITA:
                jogador1->pontuacao++;
                gw->ultimoPontuar = jogador1;
                pararJogo( gw );
                break;
            case COLISAO_LATERAL_BOLA_NENHUMA:
                break;
        }

        resolverColisaoBolaJogador( bola, jogador1 );
        resolverColisaoBolaJogador( bola, jogador2 );

    } else if ( gw->estado == ESTADO_JOGO_PARADO ) {

        if ( IsKeyPressed( KEY_ENTER ) ) {

            gw->estado = ESTADO_JOGO_EXECUTANDO;

            float velocidadeMovimentoBola;

            if ( gw->ultimoPontuar == jogador1 ) {
                velocidadeMovimentoBola = VELOCIDADE_MOVIMENTO_BOLA;
            } else if ( gw->ultimoPontuar == jogador2 ) {
                velocidadeMovimentoBola = -VELOCIDADE_MOVIMENTO_BOLA;
            } else if ( GetRandomValue( 0, 1 ) == 0 ) {
                velocidadeMovimentoBola = VELOCIDADE_MOVIMENTO_BOLA;
            } else {
                velocidadeMovimentoBola = -VELOCIDADE_MOVIMENTO_BOLA;
            }

            bola->vel = (Vector2) {
                .x = velocidadeMovimentoBola,
                .y = GetRandomValue( 0, 1 ) == 0 ? VELOCIDADE_MOVIMENTO_BOLA : -VELOCIDADE_MOVIMENTO_BOLA
            };

        }

        if ( IsKeyPressed( KEY_R ) ) {
            recomecarJogo( gw );
        }

    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    float largura = 6;
    float altura = GetScreenHeight() / 30;
    for ( int i = 0; i < altura + 5; i++ ) {
        DrawRectangle( GetScreenWidth() / 2 - largura / 2, altura * i * 2, largura, altura, WHITE );
    }

    desenharJogador( &gw->jogador1 );
    desenharJogador( &gw->jogador2 );
    desenharBola( &gw->bola );
    desenharPlacar( gw );

    EndDrawing();

}

void resolverColisaoBolaJogador( Bola *bola, Jogador *jogador ) {

    if ( verificarColisaoBolaJogador( bola, jogador ) ) {

        // indo para a direita
        if ( bola->vel.x > 0.0f ) {
            bola->pos.x = jogador->pos.x - ( jogador->dim.x / 2 ) - bola->raio;
        } else if ( bola->vel.x < 0.0f ) { // indo para a esquerda
            bola->pos.x = jogador->pos.x + ( jogador->dim.x / 2 ) + bola->raio;
        }

        bola->vel.x = -bola->vel.x;

    }

}

void pararJogo( GameWorld *gw ) {

    gw->estado = ESTADO_JOGO_PARADO;

    gw->jogador1.pos.y = GetScreenHeight() / 2;
    gw->jogador2.pos.y = GetScreenHeight() / 2;

    gw->bola.pos = (Vector2) {
        GetScreenWidth() / 2,
        GetScreenHeight() / 2,
    };

}

void recomecarJogo( GameWorld *gw ) {
    
    pararJogo( gw );
    gw->ultimoPontuar = NULL;
    gw->jogador1.pontuacao = 0;
    gw->jogador2.pontuacao = 0;

}

void desenharPlacar( GameWorld *gw ) {

    int tamanhoFonte = 40;
    int margem = 30;
    const char *pontuacao1 = TextFormat( "%d", gw->jogador1.pontuacao, gw->jogador2.pontuacao );
    const char *pontuacao2 = TextFormat( "%d", gw->jogador2.pontuacao, gw->jogador2.pontuacao );
    int larguraPontuacao1 = MeasureText( pontuacao1, tamanhoFonte );

    DrawText( pontuacao1, GetScreenWidth() / 2 - larguraPontuacao1 - margem, margem, tamanhoFonte, WHITE );
    DrawText( pontuacao2, GetScreenWidth() / 2 + margem, margem, tamanhoFonte, WHITE );

}
