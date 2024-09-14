#pragma once

#include "raylib/raylib.h"

typedef struct Jogador {

    Vector2 pos;
    Vector2 vel;
    Vector2 dim;

    Color cor;

    int pontuacao;

} Jogador;

Jogador criarJogador( Vector2 pos, Vector2 vel, Vector2 dim, Color cor );
void processarEntradaJogador( Jogador *jogador, int keyCima, int keyBaixo, float velocidadeMovimento );
void atualizarJogador( Jogador *jogador, float delta );
void desenharJogador( Jogador *jogador );
