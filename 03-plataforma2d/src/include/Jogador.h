#pragma once

#include <stdbool.h>

#include "Bloco.h"
#include "Item.h"
#include "Inimigo.h"
#include "SondaColisao.h"
#include "EstadoPosicao.h"
#include "TipoColisao.h"

#include "raylib/raylib.h"

typedef enum PosicaoSondaColisaoJogador {
    POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA,
    POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO,
    POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA,
    POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO,
    POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA,
    POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA,
    POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA,
    POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA
} PosicaoSondaColisaoJogador;

typedef struct Jogador {

    Vector2 pos;
    Vector2 vel;
    Vector2 dim;

    float velocidadeCaminhada;
    float velocidadeCorrida;
    float velocidadePulo;
    float velocidadeMaximaQueda;

    Color cor;

    EstadoPosicao estadoPosicao;
    bool correndo;
    bool viradoDireita;

    int quantidadeItensPegos;
    int pontos;
    int vida;
    int vidaMaxima;

    Animacao *animacaoEsquerda;
    Animacao *animacaoDireita;

    SondaColisao sondasColisao[8];

} Jogador;

Jogador criarJogador( Vector2 pos, Vector2 dim, float velocidadeCaminhada, float velocidadePulo, Color cor, Animacao *animacaoEsquerda, Animacao *animacaoDireita );
void processarEntradaJogador( Jogador *jogador );
void atualizarJogador( Jogador *jogador, float delta );
void desenharJogador( Jogador *jogador );

void atualizarSondasColisaoJogador( Jogador *jogador );

void resolverColisaoJogadorBlocos( Jogador *jogador, int quantidadeLinhas, int quantidadeColunas, Bloco *blocos );
TipoColisao checarColisaoJogadorBloco( Jogador *jogador, Bloco *bloco, bool checarSondas );

void resolverColisaoJogadorItens( Jogador *jogador, int quantidadeItens, Item *itens );
TipoColisao checarColisaoJogadorItem( Jogador *jogador, Item *item );

void resolverColisaoJogadorInimigos( Jogador *jogador, int quantidadeInimigos, Inimigo *inimigos );
TipoColisao checarColisaoJogadorInimigo( Jogador *jogador, Inimigo *inimigo, bool checarSondas );