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
#include "Bloco.h"
#include "Item.h"
#include "Inimigo.h"

const float GRAVIDADE = 10.0f;
const float DIMENSAO_TILES = 32.0f;

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    //GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    GameWorld *gw = (GameWorld*) calloc( 1, sizeof( GameWorld ) );

    gw->jogador = criarJogador(
        (Vector2) {
            .x = GetScreenWidth() / 2,
            .y = GetScreenHeight() / 2
        },
        (Vector2) {
            .x = 32,
            .y = 40
        },
        200.0f,
        -350.0f,
        BLUE,
        rm.animacaoJogadorEsquerda,
        rm.animacaoJogadorDireita
    );

    atualizarSondasColisaoJogador( &gw->jogador );

    const char *mapa = 
        "D                                                                 C\n"
        "D                                                                 C\n"
        "D                                                                 C\n"
        "D                                                                 C\n"
        "D                                                                 C\n"
        "D           j                                                     C\n"
        "D                                                                 C\n"
        "D       IIIIIIIII                                                 C\n"
        "D                                                                 C\n"
        "D     i  i  i  i  i                                               C\n"
        "D    IIIIIIIIIIIIIII                                              C\n"
        "D                                                                 C\n"
        "D                        e  e  e  e                               C\n"
        "HBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBG\n"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

    processarMapa( gw, mapa, DIMENSAO_TILES );

    gw->camera = (Camera2D) {
        .offset = { GetScreenWidth() / 2, GetScreenHeight() / 2 },
        .target = gw->jogador.pos,
        .rotation = 0.0f,
        .zoom = 1.0f
    };

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
    Bloco *blocos = gw->blocos;

    processarEntradaJogador( jogador );
    atualizarJogador( jogador, delta );
    atualizarSondasColisaoJogador( jogador );

    resolverColisaoJogadorBlocos( jogador, gw->linhasMapa, gw->colunasMapa, blocos );
    atualizarSondasColisaoJogador( jogador );

    for ( int i = 0; i < gw->quantidadeItens; i++ ) {
        atualizarItem( &gw->itens[i], delta );
    }
    resolverColisaoJogadorItens( jogador, gw->quantidadeItens, gw->itens );

    for ( int i = 0; i < gw->quantidadeInimigos; i++ ) {
        Inimigo *inimigo = &gw->inimigos[i];
        atualizarInimigo( inimigo, delta );
        atualizarSondasColisaoInimigo( inimigo );
        resolverColisaoInimigoBlocos( inimigo, gw->linhasMapa, gw->colunasMapa, blocos );
    }

    resolverColisaoJogadorInimigos( jogador, gw->quantidadeInimigos, gw->inimigos );
    atualizarSondasColisaoJogador( jogador );

    atualizarCamera( gw );

    tocarMusica();

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );
    BeginMode2D( gw->camera );

    for ( int i = 0; i < gw->linhasMapa; i++ ) {
        for ( int j = 0; j < gw->colunasMapa; j++ ) {
            Bloco *bloco = &gw->blocos[i*gw->colunasMapa+j];
            if ( bloco->existe ) {
                desenharBloco( bloco );
            }
        }
    }

    for ( int i = 0; i < gw->quantidadeItens; i++ ) {
        desenharItem( &gw->itens[i] );
    }

    for ( int i = 0; i < gw->quantidadeInimigos; i++ ) {
        desenharInimigo( &gw->inimigos[i] );
    }

    desenharJogador( &gw->jogador );

    EndMode2D();

    desenharHud( gw );

    EndDrawing();

}

void processarMapa( GameWorld *gw, const char *dadosMapa, float dimensaoBlocos ) {

    // passada 1: contagem de linhas, colunas, itens e inimigos
    const char *simbolo = dadosMapa;
    int quantidadeLinhas = 0;
    int quantidadeColunas = 0;
    int quantidadeItens = 0;
    int quantidadeInimigos = 0;

    int colunaAtual = 0;

    while ( *simbolo != '\0' ) {
        if ( *simbolo == '\n' ) {
            quantidadeLinhas++;
            colunaAtual = 0;
        } else {
            colunaAtual++;
            if ( quantidadeColunas < colunaAtual ) {
                quantidadeColunas = colunaAtual;
            }
            switch ( *simbolo ) {
                case 'i': quantidadeItens++; break;
                case 'e': quantidadeInimigos++; break;
            }
        }
        simbolo++;
    }

    gw->linhasMapa = quantidadeLinhas;
    gw->colunasMapa = quantidadeColunas;
    gw->blocos = (Bloco*) calloc( quantidadeLinhas * quantidadeColunas, sizeof( Bloco ) );

    gw->quantidadeItens = quantidadeItens;
    gw->itens = (Item*) malloc( quantidadeItens * sizeof( Item ) );

    gw->quantidadeInimigos = quantidadeInimigos;
    gw->inimigos = (Inimigo*) malloc( quantidadeInimigos * sizeof( Inimigo ) );
    
    // passada 2: criação
    simbolo = dadosMapa;

    int itemAtual = 0;
    int inimigoAtual = 0;

    for ( int i = 0; i < quantidadeLinhas; i++ ) {

        for ( int j = 0; j < quantidadeColunas; j++ ) {

            switch ( *simbolo ) {

                case 'j':
                    gw->jogador.pos = (Vector2) {
                        .x = j * dimensaoBlocos,
                        .y = i * dimensaoBlocos
                    };
                    break;
                
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                    gw->blocos[i * quantidadeColunas + j] = criarBloco(
                        (Vector2) {
                            .x = j * dimensaoBlocos,
                            .y = i * dimensaoBlocos
                        },
                        (Vector2) {
                            .x = dimensaoBlocos,
                            .y = dimensaoBlocos
                        },
                        GREEN,
                        selecionarTile( *simbolo )
                    );
                    break;

                case 'i':
                    gw->itens[itemAtual++] = criarItem(
                        (Vector2) {
                            .x = j * dimensaoBlocos,
                            .y = i * dimensaoBlocos
                        },
                        (Vector2) {
                            .x = 24.0f,
                            .y = dimensaoBlocos
                        },
                        YELLOW,
                        rm.animacaoItem
                    );
                    break;

                case 'e':
                    gw->inimigos[inimigoAtual++] = criarInimigo(
                        (Vector2) {
                            .x = j * dimensaoBlocos,
                            .y = i * dimensaoBlocos
                        },
                        (Vector2) {
                            .x = dimensaoBlocos,
                            .y = dimensaoBlocos
                        },
                        100.0f,
                        RED,
                        rm.animacaoInimigoEsquerda, 
                        rm.animacaoInimigoDireita
                    );
                    break;
                
            }

            simbolo++;

        }

        if ( *simbolo == '\n' ) {
            simbolo++;
        }

    }

}

void atualizarCamera( GameWorld *gw ) {
    gw->camera.target = gw->jogador.pos;
}

void desenharHud( GameWorld *gw ) {

    int larguraVida = 100;
    float percentualVida = gw->jogador.vida / (float) gw->jogador.vidaMaxima;
    int larguraPercentual = (int) ( larguraVida * percentualVida );
    DrawRectangle( 10, 10, larguraPercentual, 16, GREEN );
    DrawRectangleLines( 10, 10, larguraVida, 16, BLACK );

    DrawText( TextFormat( "Itens: %d", gw->jogador.quantidadeItensPegos ), 10, 30, 20, BLACK );
    DrawText( TextFormat( "Pontos: %d", gw->jogador.pontos ), 10, 50, 20, BLACK );
    DrawFPS( 10, 70 );

}

void tocarMusica( void ) {
    if ( !IsMusicStreamPlaying( rm.musica ) ) {
        PlayMusicStream( rm.musica );
    }
    UpdateMusicStream( rm.musica );
}

Texture2D selecionarTile( char simbolo ) {

    switch ( simbolo ) {
        case 'A': return rm.tileA;
        case 'B': return rm.tileB;
        case 'C': return rm.tileC;
        case 'D': return rm.tileD;
        case 'E': return rm.tileE;
        case 'F': return rm.tileF;
        case 'G': return rm.tileG;
        case 'H': return rm.tileH;
        case 'I': return rm.tileI;
        default : return rm.tileA;
    }

}
