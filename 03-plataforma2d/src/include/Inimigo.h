#pragma once

#include "Animacao.h"
#include "SondaColisao.h"
#include "EstadoPosicao.h"
#include "TipoColisao.h"

#include "raylib/raylib.h"

typedef enum PosicaoSondaColisaoInimigo {
    POSICAO_SONDA_COLISAO_INIMIGO_ESQUERDA,
    POSICAO_SONDA_COLISAO_INIMIGO_DIREITA,
    POSICAO_SONDA_COLISAO_INIMIGO_CIMA,
    POSICAO_SONDA_COLISAO_INIMIGO_BAIXO
} PosicaoSondaColisaoInimigo;

typedef struct Inimigo {

    Vector2 pos;
    Vector2 dim;
    Vector2 vel;
    float velocidadeCaminhada;
    float velocidadeMaximaQueda;

    Color cor;

    EstadoPosicao estadoPosicao;
    bool vivo;
    bool viradoDireita;
    int pontosAoSerMorto;

    Animacao *animacaoEsquerda;
    Animacao *animacaoDireita;

    SondaColisao sondasColisao[4];

} Inimigo;

Inimigo criarInimigo( Vector2 pos, Vector2 dim, float velocidadeCaminhada, Color cor, Animacao *animacaoEsquerda, Animacao *animacaoDireita );
void atualizarInimigo( Inimigo *inimigo, float delta );
void desenharInimigo( Inimigo *inimigo );

void atualizarSondasColisaoInimigo( Inimigo *inimigo );

void resolverColisaoInimigoBlocos( Inimigo *inimigo, int quantidadeLinhas, int quantidadeColunas, Bloco *blocos );
TipoColisao checarColisaoInimigoBloco( Inimigo *inimigo, Bloco *bloco, bool checarSondas );