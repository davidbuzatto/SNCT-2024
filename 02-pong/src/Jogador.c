#include "Jogador.h"
#include "raylib.h"

Jogador criarJogador( Vector2 pos, Vector2 vel, Vector2 dim, Color cor ) {

    return (Jogador){
        .pos = pos,
        .vel = vel,
        .dim = dim, 
        .cor = cor,
        .pontuacao = 0
    };

}

void processarEntradaJogador( Jogador *jogador, int idCima, int idBaixo, float velocidadeMovimento ) {

    if ( IsKeyDown( idCima ) ) {
        jogador->vel.y = -velocidadeMovimento;
    } else if ( IsKeyDown( idBaixo ) ) {
        jogador->vel.y = velocidadeMovimento;
    } else {
        jogador->vel.y = 0.0f;
    }

}

void atualizarJogador( Jogador *jogador, float delta ) {

    jogador->pos.y += jogador->vel.y * delta;

    if ( jogador->pos.y + jogador->dim.y / 2 >= GetScreenHeight() ) {
        jogador->pos.y = GetScreenHeight() - jogador->dim.y / 2;
    } else if ( jogador->pos.y - jogador->dim.y / 2 <= 0 ) {
        jogador->pos.y = jogador->dim.y / 2;
    }

}

void desenharJogador( Jogador *jogador ) {

    DrawRectangle( 
        jogador->pos.x - jogador->dim.x / 2,
        jogador->pos.y - jogador->dim.y / 2,
        jogador->dim.x,
        jogador->dim.y,
        jogador->cor
    );

}
