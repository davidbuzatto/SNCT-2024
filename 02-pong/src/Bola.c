#include "Bola.h"
#include "Jogador.h"
#include "raylib/raylib.h"

Bola criarBola( Vector2 pos, Vector2 vel, float raio, Color cor ) {
    return (Bola){
        .pos = pos,
        .vel = vel,
        .raio = raio,
        .cor = cor
    };
}

ColisaoLateralBola atualizarBola( Bola *bola, float delta ) {

    bola->pos.x += bola->vel.x * delta;
    bola->pos.y += bola->vel.y * delta;

    if ( bola->pos.x + bola->raio >= GetScreenWidth() ) {
        /*bola->pos.x = GetScreenWidth() - bola->raio;
        bola->vel.x = -bola->vel.x;*/
        bola->vel.x = 0.0f;
        bola->vel.y = 0.0f;
        return COLISAO_LATERAL_BOLA_DIREITA;
    } else if ( bola->pos.x - bola->raio <= 0.0f ) {
        /*bola->pos.x = bola->raio;
        bola->vel.x = -bola->vel.x;*/
        bola->vel.x = 0.0f;
        bola->vel.y = 0.0f;
        return COLISAO_LATERAL_BOLA_ESQUERDA;
    }

    if ( bola->pos.y + bola->raio >= GetScreenHeight() ) {
        bola->pos.y = GetScreenHeight() - bola->raio;
        bola->vel.y = -bola->vel.y;
    } else if ( bola->pos.y - bola->raio <= 0.0f ) {
        bola->pos.y = bola->raio;
        bola->vel.y = -bola->vel.y;
    }

    return COLISAO_LATERAL_BOLA_NENHUMA;

}

void desenharBola( Bola *bola ) {
    DrawCircle( bola->pos.x, bola->pos.y, bola->raio, bola->cor );
}

bool verificarColisaoBolaJogador( Bola *bola, Jogador *jogador ) {
    
    Rectangle jogadorRec = (Rectangle){
        .x = jogador->pos.x - jogador->dim.x / 2,
        .y = jogador->pos.y - jogador->dim.y / 2,
        .width = jogador->dim.x,
        .height = jogador->dim.y
    };

    if ( CheckCollisionCircleRec( bola->pos, bola->raio, jogadorRec ) ) {
        return true;
    }

    return false;

}