/**
 * @file ResourceManager.c
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "Animacao.h"
#include "utils.h"

#include "raylib/raylib.h"

ResourceManager rm = { 0 };

void loadResourcesResourceManager( void ) {

    rm.tileA = LoadTexture( "resources/imagens/tiles/tileA.png");
    rm.tileB = LoadTexture( "resources/imagens/tiles/tileB.png");
    rm.tileC = LoadTexture( "resources/imagens/tiles/tileC.png");
    rm.tileD = LoadTexture( "resources/imagens/tiles/tileD.png");
    rm.tileE = LoadTexture( "resources/imagens/tiles/tileE.png");
    rm.tileF = LoadTexture( "resources/imagens/tiles/tileF.png");
    rm.tileG = LoadTexture( "resources/imagens/tiles/tileG.png");
    rm.tileH = LoadTexture( "resources/imagens/tiles/tileH.png");
    rm.tileI = LoadTexture( "resources/imagens/tiles/tileI.png");

    rm.jogadorD0 = LoadTexture( "resources/imagens/sprites/jogador0.png");
    rm.jogadorD1 = LoadTexture( "resources/imagens/sprites/jogador1.png");
    rm.jogadorE0 = inverterTextura2DHorizontal( rm.jogadorD0 );
    rm.jogadorE1 = inverterTextura2DHorizontal( rm.jogadorD1 );

    rm.item0 = LoadTexture( "resources/imagens/sprites/item0.png");
    rm.item1 = LoadTexture( "resources/imagens/sprites/item1.png");
    rm.item2 = LoadTexture( "resources/imagens/sprites/item2.png");
    rm.item3 = LoadTexture( "resources/imagens/sprites/item3.png");

    rm.inimigoD0 = LoadTexture( "resources/imagens/sprites/inimigo0.png");
    rm.inimigoD1 = LoadTexture( "resources/imagens/sprites/inimigo1.png");
    rm.inimigoE0 = inverterTextura2DHorizontal( rm.inimigoD0 );
    rm.inimigoE1 = inverterTextura2DHorizontal( rm.inimigoD1 );

    rm.pulo = LoadSound( "resources/efeitosSonoros/pulo.wav" );
    rm.item = LoadSound( "resources/efeitosSonoros/item.wav" );
    rm.batida = LoadSound( "resources/efeitosSonoros/batida.wav" );

    rm.musica = LoadMusicStream( "resources/musicas/musica.mp3" );

    float tempoAnimacaoJogador = 0.15f;
    Texture2D texturasJogadorEsquerda[] = { rm.jogadorE0, rm.jogadorE1 };
    Texture2D texturasJogadorDireita[] = { rm.jogadorD0, rm.jogadorD1 };
    rm.animacaoJogadorEsquerda = criarAnimacao( texturasJogadorEsquerda, 2, tempoAnimacaoJogador );
    rm.animacaoJogadorDireita = criarAnimacao( texturasJogadorDireita, 2, tempoAnimacaoJogador );

    Texture2D texturasItens[] = { rm.item0, rm.item1, rm.item2, rm.item3 };
    rm.animacaoItem = criarAnimacao( texturasItens, 4, 0.5f );

    float tempoAnimacaoInimigo = 0.6f;
    Texture2D texturasInimigoEsquerda[] = { rm.inimigoE0, rm.inimigoE1 };
    Texture2D texturasInimigoDireita[] = { rm.inimigoD0, rm.inimigoD1 };
    rm.animacaoInimigoEsquerda = criarAnimacao( texturasInimigoEsquerda, 2, tempoAnimacaoInimigo );
    rm.animacaoInimigoDireita = criarAnimacao( texturasInimigoDireita, 2, tempoAnimacaoInimigo );

}

void unloadResourcesResourceManager( void ) {

    destruirAnimacao( rm.animacaoJogadorEsquerda );
    destruirAnimacao( rm.animacaoJogadorDireita );
    destruirAnimacao( rm.animacaoItem );
    destruirAnimacao( rm.animacaoInimigoEsquerda );
    destruirAnimacao( rm.animacaoInimigoDireita );

    UnloadTexture( rm.tileA );
    UnloadTexture( rm.tileB );
    UnloadTexture( rm.tileC );
    UnloadTexture( rm.tileD );
    UnloadTexture( rm.tileE );
    UnloadTexture( rm.tileF );
    UnloadTexture( rm.tileG );
    UnloadTexture( rm.tileH );
    UnloadTexture( rm.tileI );

    UnloadTexture( rm.jogadorE0 );
    UnloadTexture( rm.jogadorE1 );
    UnloadTexture( rm.jogadorD0 );
    UnloadTexture( rm.jogadorD1 );

    UnloadTexture( rm.item0 );
    UnloadTexture( rm.item1 );
    UnloadTexture( rm.item2 );
    UnloadTexture( rm.item3 );

    UnloadTexture( rm.inimigoE0 );
    UnloadTexture( rm.inimigoE1 );
    UnloadTexture( rm.inimigoD0 );
    UnloadTexture( rm.inimigoD1 );

    UnloadSound( rm.pulo );
    UnloadSound( rm.item );
    UnloadSound( rm.batida );

    UnloadMusicStream( rm.musica );

}