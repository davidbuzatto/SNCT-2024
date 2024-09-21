#pragma once

#include "Bloco.h"
#include "EstadoPosicao.h"
#include "raylib/raylib.h"

typedef struct Jogador {

    Vector3 pos;
    Vector3 vel;
    Vector3 dim;

    float velocidadeCaminhada;
    float velocidadePulo;
    float velocidadeMaximaQueda;

    Color cor;

    EstadoPosicao estadoPosicao;

} Jogador;

Jogador criarJogador( Vector3 pos, Vector3 dim, float velocidadeCaminhada, float velocidadePulo, Color cor );
void processarEntradaJogador( Jogador *jogador );
void atualizarJogador( Jogador *jogador, float delta );
void desenharJogador( Jogador *jogador );
void resolverColisaoJogadorChao( Jogador *jogador, Bloco *chao );
BoundingBox obterBoundingBoxJogador( Jogador *jogador );