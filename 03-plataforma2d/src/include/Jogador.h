#pragma once

#include <stdbool.h>

#include "Bloco.h"
#include "SondaColisao.h"
#include "raylib/raylib.h"

typedef enum EstadoPosicaoJogador {
    ESTADO_POSICAO_JOGADOR_NO_CHAO,
    ESTADO_POSICAO_JOGADOR_PULANDO,
    ESTADO_POSICAO_JOGADOR_CAINDO
} EstadoPosicaoJogador;

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

typedef enum TipoColisaoJogadorBloco {
    TIPO_COLISAO_JOGADOR_BLOCO_NENHUMA,
    TIPO_COLISAO_JOGADOR_BLOCO_INTERSECCAO,
    TIPO_COLISAO_JOGADOR_BLOCO_ESQUERDA,
    TIPO_COLISAO_JOGADOR_BLOCO_DIREITA,
    TIPO_COLISAO_JOGADOR_BLOCO_CIMA,
    TIPO_COLISAO_JOGADOR_BLOCO_BAIXO
} TipoColisaoJogadorBloco;

typedef struct Jogador {

    Vector2 pos;
    Vector2 vel;
    Vector2 dim;

    float velocidadeCaminhada;
    float velocidadePulo;
    float velocidadeMaximaQueda;

    Color cor;

    EstadoPosicaoJogador estadoPosicao;

    SondaColisao sondasColisao[8];

} Jogador;

Jogador criarJogador( Vector2 pos, Vector2 vel, Vector2 dim, float velocidadeCaminhada, float velocidadePulo, Color cor );
void processarEntradaJogador( Jogador *jogador );
void atualizarJogador( Jogador *jogador, float delta );
void desenharJogador( Jogador *jogador );

void atualizarSondasColisaoJogador( Jogador *jogador );
void resolverColisaoJogadorBlocos( Jogador *jogador, int quantidadeBlocos, Bloco *blocos );
TipoColisaoJogadorBloco checarColisaoJogadorBloco( Jogador *jogador, Bloco *bloco, bool checarSondas );