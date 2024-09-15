#pragma once

#include "Animacao.h"
#include "SondaColisao.h"

#include "raylib/raylib.h"

typedef enum EstadoPosicaoInimigo {
    ESTADO_POSICAO_INIMIGO_NO_CHAO,
    ESTADO_POSICAO_INIMIGO_PULANDO,
    ESTADO_POSICAO_INIMIGO_CAINDO
} EstadoPosicaoInimigo;

typedef enum PosicaoSondaColisaoInimigo {
    POSICAO_SONDA_COLISAO_INIMIGO_ESQUERDA,
    POSICAO_SONDA_COLISAO_INIMIGO_DIREITA,
    POSICAO_SONDA_COLISAO_INIMIGO_CIMA,
    POSICAO_SONDA_COLISAO_INIMIGO_BAIXO
} PosicaoSondaColisaoInimigo;

typedef enum TipoColisaoInimigo {
    TIPO_COLISAO_INIMIGO_NENHUMA,
    TIPO_COLISAO_INIMIGO_INTERSECCAO,
    TIPO_COLISAO_INIMIGO_ESQUERDA,
    TIPO_COLISAO_INIMIGO_DIREITA,
    TIPO_COLISAO_INIMIGO_CIMA,
    TIPO_COLISAO_INIMIGO_BAIXO
} TipoColisaoInimigo;

typedef struct Inimigo {

    Vector2 pos;
    Vector2 dim;
    Vector2 vel;
    float velocidadeCaminhada;
    float velocidadeMaximaQueda;

    Color cor;

    EstadoPosicaoInimigo estadoPosicao;
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
TipoColisaoInimigo checarColisaoInimigoBloco( Inimigo *inimigo, Bloco *bloco, bool checarSondas );